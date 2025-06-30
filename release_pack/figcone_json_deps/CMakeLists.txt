cmake_minimum_required(VERSION 3.18)

project(figcone_json_deps)
include(seal_lake.cmake)

SealLake_v040_Bundle(
        NAME figcone_tree
        URL https://github.com/kamchatka-volcano/figcone_tree/releases/download/v2.2.0/figcone_tree-v2.2.0.zip
        SKIP_LOAD
        DESTINATION deps/figcone_tree
)

SealLake_v040_Bundle(
        NAME figcone_nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
        SKIP_LOAD
        DIRECTORIES include
        DESTINATION deps/figcone_nlohmann_json/
        TEXT_REPLACEMENTS
            "nlohmann::" "figcone::json::nlohmann::"
            "namespace nlohmann" "namespace figcone::json::nlohmann"
            "\${PROJECT_NAME}" "figcone_nlohmann_json"
)