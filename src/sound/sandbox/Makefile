CC=gcc
CFLAGS=-g -O2 -Wall -I/usr/include/SDL2 -I/usr/include/SDL -I ../../../include -D_GNU_SOURCE=1 -D_REENTRANT 
LDFLAGS= -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_mixer

PROGRAMS=$(basename $(wildcard *.c))

%: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS) *.o
new: clean all

main: 
	gcc -o main $(CFLAGS) -L/usr/lib/ main.c -Wl,--allow-shlib-undefined -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lrt

tts:
	gcc test-tts.c ../src/tts.c -lespeak-ng -o test-tts -I ../../../include/

