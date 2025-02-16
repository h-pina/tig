add_executable(tig main.c)
set(CMAKE_BUILD_TYPE Debug)
target_link_libraries(tig PUBLIC tig_lib crypto)
target_include_directories(tig PUBLIC "${PROJECT_SOURCE_DIR}/src")
