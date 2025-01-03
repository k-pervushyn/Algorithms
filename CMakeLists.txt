cmake_minimum_required(VERSION 3.29)
project(algorithms C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE C_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

file(GLOB_RECURSE CPP_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(algorithms test/main.c ${C_SOURCE_FILES})
