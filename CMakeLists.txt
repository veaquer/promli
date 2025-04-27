cmake_minimum_required(VERSION 3.16)

project(promli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SRC
    "src/core/*.cpp"
    "src/lua/*.cpp"
    "src/utils/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "include/core/*.h"
    "include/lua/*.h"
    "include/utils/*.h"
)




add_executable(promli 
    src/main.cpp ${SRC} ${HEADERS})

target_include_directories(promli PRIVATE include)
target_include_directories(promli PRIVATE external/sol2/include)
target_include_directories(promli PRIVATE external/curl/include)
target_include_directories(promli PRIVATE /usr/include) # Lua headers
target_link_libraries(promli PRIVATE lua)               # Lua library
find_package(CURL REQUIRED)
target_link_libraries(promli PRIVATE lua ${CURL_LIBRARIES})
target_include_directories(promli PRIVATE ${CURL_INCLUDE_DIRS})
