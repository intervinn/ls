setup:
	meson setup build --wipe

compile:
	meson compile -C build

run: compile
	./build/src/lstuff