test_inventory_graphics: test_inventory_graphics.c inventory_graphics.c
	cc test_inventory_graphics.c inventory_graphics.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../../include/ -I../gdl/read_gdl.h -o test_inventory_graphics

clean:
	rm inventory_graphics test_inventory_graphics
