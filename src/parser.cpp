#include <figcone_json/parser.h>
#include <figcone_tree/errors.h>
#include <nlohmann/json.hpp>
#include <regex>

namespace figcone::json {

namespace {
void parseJson(const nlohmann::json& json, figcone::TreeNode& node)
{
    for (auto& [key, value] : json.items()) {
        if (value.is_object()) {
            auto& newNode = node.asItem().addNode(key);
            parseJson(value, newNode);
        }
        else if (value.is_array()) {
            if (!value.empty() && value.front().is_object()) {
                auto& newNode = node.asItem().addNodeList(key);
                for (auto& item : value)
                    parseJson(item, newNode.asList().emplaceBack());
            }
            else {
                auto valuesList = std::vector<std::string>{};
                for (auto& item : value)
                    valuesList.emplace_back(item.get<std::string>());

                node.asItem().addParamList(key, valuesList);
            }
        }
        else
            node.asItem().addParam(key, value.get<std::string>());
    }
}

void parseJsonRootList(const nlohmann::json& json, figcone::TreeNode& node)
{
    if (json.is_array()) {
        for (auto& item : json)
            parseJson(item, node.asList().emplaceBack());
    }
    else {
        parseJson(json, node.asList().emplaceBack());
    }
}

ConfigError makeConfigError(const nlohmann::json::exception& e)
{
    const auto message = std::string{e.what()};
    static const auto regex = std::regex{R"(.*\line (\d+), column (\d+): (.*))"};
    auto match = std::smatch{};
    if (std::regex_search(message, match, regex)) {
        auto line = std::stoi(match[1]);
        auto column = std::stoi(match[2]);
        auto error = match[3].str();
        if (!error.empty())
            error[0] = static_cast<char>(std::toupper(error[0]));

        return {error, figcone::StreamPosition{line, column}};
    }
    return {e.what()};
}
} //namespace

Tree Parser::parse(std::istream& stream)
{
    auto json = nlohmann::json{};
    try {
        stream >> json;
    }
    catch (const nlohmann::json::exception& e) {
        throw makeConfigError(e);
    }

    auto treeRoot = figcone::makeTreeRootList();
    parseJsonRootList(json, *treeRoot);
    return Tree{std::move(treeRoot)};
}

} //namespace figcone::json