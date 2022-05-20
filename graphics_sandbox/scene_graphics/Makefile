scene_graphics: scene_graphics.c
	cc scene_graphics.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I./ -I../../include/gdl -I../../include/game-state -I../../include -o scene_graphics

test_scene_graphics: test_scene_graphics.c scene_graphics.c
	gcc test_scene_graphics -Wall -Wextra -O2 -g -I./ -I../../include/gdl -I../../include/game-state -I../../include -o test_scene_graphics