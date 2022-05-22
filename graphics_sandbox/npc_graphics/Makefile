all: npc_graphics test

npc_graphics: npc_graphics.c
	cc npc_graphics.c main.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -o npc_graphics

test:
	cc test_npc_graphics.c npc_graphics.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I./ -o test_npc_graphics

clean:
	rm npc_graphics
