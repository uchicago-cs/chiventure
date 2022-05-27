quest_graphics: quest_graphics.c main.c
	cc quest_graphics.c main.c -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I. -o quest_graphics-1

test_quest_graphics: test_quest_graphics.c quest_graphics.c
	cc test_quest_graphics.c quest_graphics.c  -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../ -o test_quest_graphics -lcriterion

clean:
	rm quest_graphics test_quest_graphics
