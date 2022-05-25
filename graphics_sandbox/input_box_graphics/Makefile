all: input_box_graphics test

input_box_graphics: input_box_graphics.c main.c
	cc input_box_graphics.c main.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -I../../include/common -o input_box_graphics


test: input_box_graphics.c test_input_box_graphics.c
	cc input_box_graphics.c test_input_box_graphics.c -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -I../../include/common -o test_input_box_graphics -lcriterion

clean:
	rm input_box_graphics test_input_box_graphics