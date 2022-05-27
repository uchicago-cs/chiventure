test: test_inventory_graphics.c inventory_graphics.c
	cc inventorytest.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../../include/game-state -I../../include -I../../include/gdl -o test

test_inventory_graphics: test_inventory_graphics.c inventory_graphics.c
	cc -fPIC -g -Wall -Wextra -O2 -I../../include/game-state -I../../graphics_sandbox/gdl -I../../include/ -L../  -Wl,-rpath,. test_inventory_graphics.c inventory_graphics.c  -o test_inventory_graphics -lcriterion


inventory_graphics: inventory_graphics.c
	cc inventory_graphics.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I.  -I../../include/game-state -I../../include -I../../include/gdl -o inventory_graphics

clean:
	rm test inventory_graphics test_inventory_graphics
