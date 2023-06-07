cmake_minimum_required(VERSION 3.2)

project(main LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 98)

add_subdirectory(src)
add_subdirectory(load_png)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} opt_path)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/load_png)

target_link_libraries(${PROJECT_NAME} lodepng)