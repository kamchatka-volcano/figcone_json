cmake_minimum_required(VERSION 3.18)
project(figcone_json VERSION 1.1.0 DESCRIPTION "nlohmann::json parser adapter for figcone library")
include(external/seal_lake)

SealLake_Bundle(
        NAME figcone_nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
        TEXT_REPLACEMENTS
            "nlohmann::" "figcone::json::nlohmann::"
            "namespace nlohmann" "namespace figcone::json::nlohmann"
            "\${PROJECT_NAME}" "figcone_nlohmann_json"
)

SealLake_IsInstallEnabled(INSTALL_FIGCONE_TREE)
SealLake_Import(
        figcone_tree 2.1.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG      v2.1.0
)

SealLake_ObjectLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        SOURCES
            src/parser.cpp
        LIBRARIES figcone_nlohmann_json::figcone_nlohmann_json
        INTERFACE_LIBRARIES figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 2.1.0
)

SealLake_OptionalSubProjects(tests)