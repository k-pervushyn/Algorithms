cmake_minimum_required(VERSION 3.29)
project(c_algorithms C)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE C_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_library(c_algorithms STATIC ${C_SOURCE_FILES})

add_executable(test_c test/c_test.c)
target_link_libraries(test_c c_algorithms)
