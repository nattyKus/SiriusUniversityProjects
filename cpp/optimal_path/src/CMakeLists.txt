cmake_minimum_required(VERSION 3.2)

project(opt_path LANGUAGES CXX)
set(CMAKE_CXX_STANDERD 98)

add_library(${PROJECT_NAME} opt_path.cpp opt_path.h)