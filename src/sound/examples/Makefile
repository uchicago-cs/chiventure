CC=gcc
CFLAGS=-g -O2 -Wall -I/usr/include/SDL2 -I/usr/include/SDL -I ../../../include -D_GNU_SOURCE=1 -D_REENTRANT 
LDFLAGS= -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_mixer -lSDL2_image -lespeak-ng

PROGRAMS=$(basename $(wildcard *.c))

%: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS) *.o
new: clean all

tts:
	$(CC) $(CPPFLAGS) $(CFLAGS) ../src/tts.c test-tts.c -o test-tts $(LDFLAGS) 

