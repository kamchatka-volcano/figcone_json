#pragma once
#include <figcone_tree/tree.h>
#include <figcone_tree/iparser.h>
#include <figcone_tree/errors.h>
#include <nlohmann/json.hpp>
#include <regex>
#include <vector>
#include <string>

namespace figcone::json::detail {

inline void parseJson(const nlohmann::json& json, figcone::TreeNode& node)
{
    for (auto& [key, value]: json.items()) {
        if (value.is_object()) {
            auto& newNode = node.asItem().addNode(key);
            parseJson(value, newNode);
        } else if (value.is_array()) {
            if (!value.empty() && value.front().is_object()) {
                auto& newNode = node.asItem().addNodeList(key);;
                for (auto& item: value)
                    parseJson(item, newNode.asList().addNode());
            } else {
                auto valuesList = std::vector<std::string>{};
                for (auto& item: value)
                    valuesList.emplace_back(item.get<std::string>());

                node.asItem().addParamList(key, valuesList);
            }
        } else
            node.asItem().addParam(key, value.get<std::string>());
    }
}

inline std::tuple<figcone::StreamPosition, std::string> parseExceptionMessage(const nlohmann::json::exception& e)
{
    auto message = std::string{e.what()};
    auto regex = std::regex{R"(.*\line (\d+), column (\d+): (.*))"};
    auto match = std::smatch{};
    if (std::regex_search(message, match, regex)) {
        auto line = std::stoi(match[1]);
        auto column = std::stoi(match[2]);
        auto error = match[3].str();
        if (!error.empty())
            error[0] = static_cast<char>(std::toupper(error[0]));

        return std::make_tuple(figcone::StreamPosition{line, column}, error);
    }
    return {};
}

}

namespace figcone::json {
class Parser : public IParser {
public:
    TreeNode parse(std::istream& stream) override
    {
        auto json = nlohmann::json{};
        try {
            stream >> json;
        }
        catch (const nlohmann::json::exception& e) {
            auto [position, error] = detail::parseExceptionMessage(e);
            if (error.empty())
                throw figcone::ConfigError{e.what()};
            else
                throw figcone::ConfigError{position, error};
        }

        auto tree = figcone::makeTreeRoot();
        detail::parseJson(json, tree);
        return tree;
    }
};

}