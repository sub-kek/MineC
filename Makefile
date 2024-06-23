generate_release:
	cmake -DCMAKE_BUILD_TYPE:STRING=Debug -S . -B ./build -G Ninja
	ln -sf ./build/compile_commands.json ./

release:
	$(MAKE) generate_release
	cmake --build ./build -j 12

clean:
	rm -rf build
	rm -f compile_commands.json

run:
	./build/MineC

all:
	$(MAKE) clean
	$(MAKE) release
	$(MAKE) run
