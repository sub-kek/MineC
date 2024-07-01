BUILD_DIR = build

minec: cmake_setup cmake_compile compiler_setup run

cmake_setup:
	cmake -DCMAKE_BUILD_TYPE:STRING=Debug -S . -B ./build -G Ninja

cmake_compile:
	cmake --build ./build -j 12

compiler_setup:
	ln -sf $(BUILD_DIR)/compile_commands.json .

run:
	$(BUILD_DIR)/MineC

clean:
	rm -rf $(BUILD_DIR)
	rm -f compile_commands.json

favicon0:
	ln -sf $@.png favicon.png

favicon1:
	ln -sf $@.png favicon.png

favicon2:
	ln -sf $@.png favicon.png

.DEFAULT_GOAL := minec
.PHONY: minec cmake_setup cmake_compile compiler_setup run clean favicon0 favicon1 favicon2