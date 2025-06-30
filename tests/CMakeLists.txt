cmake_minimum_required(VERSION 3.18)
project(test_figcone_json)

set(SRC
        test_paramparser.cpp
        test_paramlistparser.cpp
        test_nodeparser.cpp
        test_nodelistparser.cpp)

if(FIGCONE_JSON_TEST_RELEASE)
    add_subdirectory(release)
endif()

SealLake_v040_GoogleTest(
        SOURCES ${SRC}
        COMPILE_FEATURES cxx_std_17
        PROPERTIES
            CXX_EXTENSIONS OFF
        LIBRARIES figcone::figcone_json
)
