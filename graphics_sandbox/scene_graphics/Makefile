main: main.c scene_graphics.c
	cc main.c scene_graphics.c  -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../ -I../../include/common -o main

test_scene_graphics: test_scene_graphics.c scene_graphics.c
	cc test_scene_graphics.c scene_graphics.c  -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../ -I../../include/common -o test_scene_graphics -lcriterion
