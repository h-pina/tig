add_executable(tig main.c)
target_link_libraries(tig PUBLIC tig_lib crypto)
target_include_directories(tig PUBLIC "${PROJECT_SOURCE_DIR}/src")
