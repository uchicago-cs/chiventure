main: map_graphics.c main.c
	cc map_graphics.c main.c -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -I../../include/common -o main



test: map_graphics.c test_map_graphics.c
	cc map_graphics.c test_map_graphics.c -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -I../../include/common -o test_map_graphics -lcriterion

clean:
	rm test_map_graphics main
