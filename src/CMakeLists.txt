set(CMAKE_BUILD_TYPE Debug)
add_library(tig_lib 
	cli.c
	init.c
	object.c
	blob.c
	tree.c
	index.c
	utils/utils.c
	logger.c
	fs.c
)

