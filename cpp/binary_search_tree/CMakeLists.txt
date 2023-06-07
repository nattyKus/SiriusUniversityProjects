cmake_minimum_required(VERSION 3.2)

project(main LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 98)

add_executable(${PROJECT_NAME} main.cpp)

add_library(tree tree.cpp tree.h)
target_link_libraries(${PROJECT_NAME} tree)