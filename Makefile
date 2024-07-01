BUILD_DIR = build

minec: cmake_setup cmake_compile compiler_setup run

favicon:
	@read -p "Enter favicon[0-2]: " favnum; \
	ln -sf favicon$$favnum.png favicon.png

cmake_setup:
	cmake -DCMAKE_BUILD_TYPE:STRING=Release -S . -B ./build -G Ninja

cmake_compile:
	cmake --build ./build -j 12

compiler_setup:
	ln -sf $(BUILD_DIR)/compile_commands.json .

run:
	$(BUILD_DIR)/MineC

clean:
	rm -rf $(BUILD_DIR)
	rm -f compile_commands.json
	rm -f favicon.png



.DEFAULT_GOAL := minec
.PHONY: minec cmake_setup cmake_compile compiler_setup run clean favicon