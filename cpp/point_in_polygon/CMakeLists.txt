cmake_minimum_required(VERSION 3.2)

project(polygon LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11) # set standard to 98 (we do not use any new feautures)

if(NOT CMAKE_BUILD_TYPE) # if CMAKE_BUILD_TYPE is undefined
    set(CMAKE_BUILD_TYPE Release) # set it to Release
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic") # Set flags for compilation (applied both to Release and Debug or any other type). NOTE: this flags are g++ specific.
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -DDEBUG") # Set additional flags for Debug builds. NOTE: this flags are g++ specific.
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG -march=native") # Set additional flags for Release builds. NOTE: this flags are g++ specific.


add_executable(poly main.cpp polygon.h polygon.cpp parse_arguments.h parse_arguments.cpp)
