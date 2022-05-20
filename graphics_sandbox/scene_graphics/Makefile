scene_graphics: scene_graphics.c
	cc scene_graphics.c main.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../ -o scene_graphics

test_scene_graphics: test_scene_graphics.c scene_graphics.c
	cc test_scene_graphics.c scene_graphics.c  -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../ -o test_scene_graphics -lcriterion