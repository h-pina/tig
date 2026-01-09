# Default target
.PHONY: all
all: 
	cmake -S . -B build -DTGT:STRING=build
	cmake --build build 
	make -C ./build/
	ln -sf ./build/main/tig ./tig

.PHONY: all
clean: 
	rm -rf ./build/*
	rm -f ./tig
	rm -rf ./.tig/

