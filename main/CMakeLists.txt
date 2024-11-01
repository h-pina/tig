add_executable(tig main.c)
target_link_libraries(tig PUBLIC tig_lib crypto)
