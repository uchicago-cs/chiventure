all: map_graphics test

map_graphics: map_graphics.c main.c
	cc map_graphics.c main.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -o map_graphics


test: map_graphics.c test_map_graphics.c
	cc map_graphics.c test_map_graphics.c -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -o test_map_graphics -lcriterion

clean:
	rm map_graphics test_map_graphics
