

# Default target
.PHONY: all
all: 
	cmake -S . -B build -DTGT:STRING=build && cmake --build build 
	make -C ./build/
	ln -sf ./build/main/tig ./tig

.PHONY: test 
test: 
	cmake -S . -B build -DTGT:STRING=test && cmake --build build 
	ctest --test-dir ./build/


.PHONY: all
clean: 
	rm -rf ./build/*
	rm -f ./tig

