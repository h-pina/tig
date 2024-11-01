

# Default target
.PHONY: all
all: 
	cmake -S . -B build && cmake --build build
	make -C ./build/
	ln -sf ./build/main/tig ./tig


.PHONY: all
clean: 
	rm -rf ./build/*
	rm ./tig

