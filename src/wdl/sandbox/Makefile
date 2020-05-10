# Makefile for loading parser

BIN = parse
SRCS = parser.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2 -g
DYN_LDFLAGS = -L /usr/lib/x86_64=linux-gnu | grep json -Wl,-rpath,/usr/lib/x86_64=linux-gnu | grep json #-L designates where to find the library.
LDLIBS = -ljson-c
LD_LIBRARY_PATH = /usr/lib/x86_64=linux-gnu | grep json

RM = rm -f

$(BIN): parser.o
	$(CC) $(DYN_LDFAGS) $^ -o $@ $(LDLIBS)

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $(patsubst %.o, %.c, $@)

.PHONY: clean

clean:
	$(RM) ${OBJS} $(BIN)
