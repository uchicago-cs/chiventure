input_box: input_box.c
	cc input_box.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -o input_box

clean:
	rm input_box
