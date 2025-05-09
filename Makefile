setup:
	meson setup builddir wipe

compile:
	meson compile -C builddir

run: compile
	./builddir/src/lstuff