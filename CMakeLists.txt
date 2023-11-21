cmake_minimum_required(VERSION 3.25)
project(n_body)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

#add_subdirectory(sdl-main)

add_executable(n_body_sdl main.cpp)


target_include_directories(n_body_sdl PUBLIC headers)