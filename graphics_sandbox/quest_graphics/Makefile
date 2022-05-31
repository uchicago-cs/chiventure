all: quest_graphics test_quest_graphics

quest_graphics: main.c quest_graphics.c
	cc main.c quest_graphics.c  -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../ -I../../include/common/ -o quest_graphics

test_quest_graphics: test_quest_graphics.c quest_graphics.c
	cc test_quest_graphics.c quest_graphics.c  -L../ -Wl,-rpath,. -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -I../ -I../../include/common/ -o test_quest_graphics -lcriterion

clean:
	rm quest_graphics test_quest_graphics