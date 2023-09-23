cmake_minimum_required(VERSION 3.25)
project(n_body)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(test main.cpp)

target_include_directories(test PUBLIC headers)

target_link_libraries(test PUBLIC ${GTEST_LIBRARIES} pthread)