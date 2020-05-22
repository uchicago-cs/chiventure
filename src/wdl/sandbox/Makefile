# Makefile for loading parser

BIN = parse
SRCS = parser.c 
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2 -c -g -I../../../include/ -I.../include/
DYN_LDFLAGS = "-L /usr/lib/x86_64=linux-gnu | grep json -L ../../../build/src/game-state/libgame-state.a" -Wl,-rpath,"/usr/lib/x86_64=linux-gnu ../../../build/src/game-state/libgame-state.a"#-L designates where to find the library.
LDLIBS = -ljson-c -l:$libgame-state.a
LD_LIBRARY_PATH = ../../../build/src/game-state/ /usr/lib/x86_64=linux-gnu | grep json 

RM = rm -f

$(BIN): parser.o ../../../build/src/game-state/libgame-state.a
	$(CC) $(DYN_LDFAGS) $< -o $@ $(LDLIBS)

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o, %.c, $@)

.PHONY: clean

clean:
	$(RM) ${OBJS} $(BIN)
