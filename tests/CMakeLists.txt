cmake_minimum_required(VERSION 3.18)
project(test_figcone_json)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(CheckPIESupported)
check_pie_supported()

set(SRC
        test_paramparser.cpp
        test_paramlistparser.cpp
        test_nodeparser.cpp
        test_nodelistparser.cpp)

add_executable(test_figcone_json ${SRC})
target_compile_features(test_figcone_json PUBLIC cxx_std_17)
set_target_properties(test_figcone_json PROPERTIES CXX_EXTENSIONS OFF POSITION_INDEPENDENT_CODE OFF)

add_test(NAME test_figcone_json COMMAND test_figcone_json)
target_link_libraries(test_figcone_json PRIVATE ${GTEST_BOTH_LIBRARIES} Threads::Threads figcone::figcone_json)
