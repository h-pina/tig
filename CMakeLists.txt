cmake_minimum_required(VERSION 3.10)
project(tig)

add_subdirectory(main)
add_subdirectory(src)
target_include_directories(tig PUBLIC "${PROJECT_SOURCE_DIR}/src")

