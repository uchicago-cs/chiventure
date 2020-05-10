# Makefile for loading parser

BIN = parse
SRCS = parser.c

CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2 -g
LDLIBS = -ljson-c

RM = rm -f

all:
	$(CC) $(CFLAGS) $(LDLIBS) -o $(BIN) $(SRCS)

clean:
	$(RM) $(BIN)
