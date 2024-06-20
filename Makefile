generate_release:
	cmake -DCMAKE_BUILD_TYPE:STRING=Relese -S . -B ./build -G Ninja
	ln -sf ./build/compile_commands.json ./

release:
	$(MAKE) generate_release
	cmake --build ./build -j $(nproc)

clean:
	rm -rf build
	rm -f compile_commands.json

run:
	./build/MineC

all:
	$(MAKE) clean
	$(MAKE) release
	$(MAKE) run
