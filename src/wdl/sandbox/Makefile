# Makefile for loading parser

BIN = parse
SRCS = parser.c 
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2 -c -g -I../../../include/ -I.../include/

DYN_LDFLAGS = -L /usr/lib/x86_64=linux-gnu | grep json -Wl,-rpath,/usr/lib/x86_64=linux-gnu | grep json #-L designates where to find the library.
LPATH = ../../../build/src/game-state/
STC_LDFLAGS = -L../../../build/src/game-state/$(LPATH)
STC_LIB = libgame-state.a

LDLIBS = -ljson-c 
LD_LIBRARY_PATH = /usr/lib/x86_64=linux-gnu | grep json

RM = rm -f

$(BIN): parser.o $(LPATH)$(STC_LIB)
	$(CC) $(DYN_LDFAGS) $(STC_LDFLAGS) $^ -o $@ -l:$(STC_LIB) $(LDLIBS) -lm

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o, %.c, $@)

.PHONY: clean

clean:
	$(RM) ${OBJS} $(BIN)
