cmake_minimum_required(VERSION 3.25)
project(n_body)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp)

target_include_directories(test PUBLIC headers)