cmake_minimum_required(VERSION 3.10)
project(kendalltau CXX)

find_package(pybind11 REQUIRED)

include_directories(include)

set(PYBIND11_CPP_STANDARD -std=c++17)

pybind11_add_module(_kt "${PROJECT_SOURCE_DIR}/src/python/_kt.cc")
