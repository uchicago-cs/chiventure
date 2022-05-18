.Phony: clean_test clean_inventory_graphics

all: test inventory_graphics

test: test_inventory_graphics.c inventory_graphics.c
	cc inventorytest.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../../include/game-state -I../../include -I../../include/gdl -o test

inventory_graphics:	inventory_graphics.c
	cc inventory_graphics.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -I../../include/game-state -I../../include -I../../include/gdl -o inventory_graphics

clean:
	rm test inventory_graphics

clean_test:
	rm test

clean_inventory_graphics:
	rm inventory_graphics