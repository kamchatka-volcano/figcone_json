cmake_minimum_required(VERSION 3.18)

project(figcone_json VERSION 0.11.0 DESCRIPTION "nlohmann::json parser adapter for figcone library")
include(GNUInstallDirs)
include(external/seal_lake)

SealLake_FindOrDownload(
        json 3.10.5
        URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

set(INSTALL_FIGCONE_TREE ON)
SealLake_FindOrDownload(
        figcone_tree 0.11.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG        cmake_maintenance
)

SealLake_HeaderOnlyLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        INCLUDES figcone_json/detail/external
        BUILD_STAGE_INCLUDES ${json_SOURCE_DIR}/include/
        LIBRARIES figcone::figcone_tree
)

SealLake_OptionalBuildSteps(
        IF_ENABLED_AND_STANDALONE tests
)

SealLake_Install(
        PATH figcone_json/detail/external
        DIRECTORIES ${json_SOURCE_DIR}/include/nlohmann
)