test: test_inventory_graphics.c inventory_graphics.c inventorytest.c
	cc inventorytest.c test_inventory_graphics.c inventory_graphics.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../../include/game-state -I../../include -I../../include/gdl -o test


clean:
	rm test inventory_graphics test_inventory_graphics
