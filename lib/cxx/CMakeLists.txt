cmake_minimum_required(VERSION 3.29)
project(cxx_algorithms CXX)

set(CMAKE_CXX_STANDARD 98)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE CXX_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(cxx_algorithms STATIC ${CXX_SOURCE_FILES})

add_executable(test_cxx test/cxx_test.cpp)
target_link_libraries(test_cxx cxx_algorithms)
