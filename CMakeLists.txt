cmake_minimum_required(VERSION 3.18)

project(figcone_json VERSION 0.10.0 DESCRIPTION "nlohmann::json parser adapter for figcone library")

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(FIGCONE_JSON_SUBPROJECT OFF)
else()
    set(FIGCONE_JSON_SUBPROJECT ON)
endif()

include(external/json)
find_package(figcone_tree 0.10.0 QUIET)
if (NOT figcone_tree_FOUND)
    message("Configuration info: figcone_tree library wasn't found on your system, downloading it from the GitHub repository")
    include (external/figcone_tree)
endif()

add_library(figcone_json INTERFACE)
add_library(figcone::figcone_json ALIAS figcone_json)

target_compile_features(figcone_json INTERFACE cxx_std_17)
target_include_directories(
        figcone_json
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_include_directories(
        figcone_json
        INTERFACE
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/figcone_json/detail/external>
)
target_include_directories(
        figcone_json
        INTERFACE
        $<BUILD_INTERFACE:${json_SOURCE_DIR}/include/>
)
target_link_libraries(figcone_json INTERFACE figcone::figcone_tree)

option(ENABLE_TESTS "Enable tests" OFF)
if (ENABLE_TESTS AND NOT FIGCONE_JSON_SUBPROJECT)
    enable_testing()
    add_subdirectory(tests)
endif()

option(INSTALL_FIGCONE_JSON "Install figcone_json library unconditionally" OFF)
if (NOT FIGCONE_JSON_SUBPROJECT OR INSTALL_FIGCONE_JSON)
    include(GNUInstallDirs)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/figcone_json DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(DIRECTORY ${json_SOURCE_DIR}/include/nlohmann        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/figcone_json/detail/external)

    set(FIGCONE_JSON_PACK_PATH ${CMAKE_INSTALL_LIBDIR}/cmake/figcone_json)
    install(TARGETS figcone_json
            EXPORT figcone_json-targets
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/figcone_json)
    install(EXPORT figcone_json-targets
            FILE figcone_jsonTargets.cmake
            NAMESPACE figcone::
            DESTINATION ${FIGCONE_JSON_PACK_PATH})

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_jsonConfigVersion.cmake
            COMPATIBILITY SameMajorVersion
            ARCH_INDEPENDENT
    )

    configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/figcone_jsonConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_jsonConfig.cmake
            INSTALL_DESTINATION ${FIGCONE_JSON_PACK_PATH}
    )

    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_jsonConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_jsonConfigVersion.cmake
            DESTINATION ${FIGCONE_JSON_PACK_PATH}
    )
endif()
