cmake_minimum_required(VERSION 3.10)
project(kendalltau CXX)

find_package(pybind11 REQUIRED)

option(HAS_TESTS "Move the test script into the build directory" ON)

include_directories(include)
set(PYBIND11_CPP_STANDARD -std=c++17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")
pybind11_add_module(_kt "${PROJECT_SOURCE_DIR}/src/python/_kt.cc")
message("-- Copying wrapper for kendall pvalue")
file(COPY ${PROJECT_SOURCE_DIR}/src/kendall.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (HAS_TESTS)
        message("-- Move test file into build directory")
        file(COPY ${PROJECT_SOURCE_DIR}/tests/test.py
                DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
