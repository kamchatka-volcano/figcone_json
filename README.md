**figcone_json** - is a [`nlohmann/json`](https://github.com/nlohmann/json) configuration parser adapter for [`figcone`](https://github.com/kamchatka-volcano/figcone) library. 


## Installation
Download and link the library from your project's CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(figcone_json
    GIT_REPOSITORY "https://github.com/kamchatka-volcano/figcone_json.git"
    GIT_TAG "origin/master"
)
#uncomment if you need to install figcone_json with your target
#set(INSTALL_FIGCONE_JSON ON)
FetchContent_MakeAvailable(figcone_json)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE figcone::figcone_json)
```

For the system-wide installation use these commands:
```
git clone https://github.com/kamchatka-volcano/figcone_json.git
cd figcone_json
cmake -S . -B build
cmake --build build
cmake --install build
```

Afterwards, you can use find_package() command to make the installed library available inside your project:
```
find_package(figcone_json 0.9.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE figcone::figcone_json)
```

## Running tests
```
cd figcone_json
cmake -S . -B build -DENABLE_TESTS=ON
cmake --build build
cd build/tests && ctest
```

## License
**figcone_json** is licensed under the [MS-PL license](/LICENSE.md)  
