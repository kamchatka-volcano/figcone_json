cmake_minimum_required(VERSION 3.18)

project(figcone_json VERSION 1.2.0 DESCRIPTION "nlohmann::json parser adapter for figcone library")
include(seal_lake.cmake)

SealLake_v040_IsInstallEnabled(INSTALL_FIGCONE_TREE)
find_package(figcone_tree 2.2.0 QUIET)
if (NOT TARGET figcone::figcone_tree)
    add_subdirectory(deps/figcone_tree)
endif()

SealLake_v040_ObjectLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        SOURCES
            src/parser.cpp
        INCLUDES
            ${CMAKE_CURRENT_LIST_DIR}/deps/figcone_nlohmann_json/include
        INTERFACE_LIBRARIES figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 2.2.0
)
