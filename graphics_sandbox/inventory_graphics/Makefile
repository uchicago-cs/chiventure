test:
	cc inventorytest.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -o test

inventory_graphics:
	cc inventory_graphics.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -o inventory_graphics

clean test:
	rm test

clean inventory_graphics:
	rm inventory_graphics