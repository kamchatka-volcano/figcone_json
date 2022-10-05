cmake_minimum_required(VERSION 3.18)
project(figcone_json VERSION 0.11.0 DESCRIPTION "nlohmann::json parser adapter for figcone library")
include(GNUInstallDirs)
include(external/seal_lake)

SealLake_Download(
        URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
        DESTINATION include/figcone_json/detail/external
        DIRECTORIES include/nlohmann
        TEXT_REPLACEMENTS
            "nlohmann::" "figcone::json::nlohmann::"
            "namespace nlohmann" "namespace figcone::json::nlohmann"
            "INCLUDE_NLOHMANN_" "INCLUDE_FIGCONE_NLOHMANN_"
)

set(INSTALL_FIGCONE_TREE ON)
SealLake_Import(
        figcone_tree 0.11.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG        cmake_maintenance
)

SealLake_HeaderOnlyLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        INCLUDES figcone_json/detail/external
        BUILD_STAGE_INCLUDES figcone_json/detail/external
        LIBRARIES figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 0.11.0
)

SealLake_OptionalBuildSteps(tests)