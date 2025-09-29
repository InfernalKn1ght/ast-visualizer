cmake_minimum_required(VERSION 3.28)

project(ast_visualizer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/app)
add_subdirectory(src/core_analyzer_lib)
add_subdirectory(src/model_lib)
add_subdirectory(src/view_lib)
