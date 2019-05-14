# Makefile for CS22000 Command Line Interface

CC = gcc
SRCS = src/cmd.c src/shell.c src/parser.c src/operations.c src/validate.c
HDRS = include/cmd.h include/shell.h include/parser.h include/validate.h
CFLAGS = -fPIC -Wall -Wextra -g -O2 -lm -I./include/ -I../common/include/
LIB = cli.a

.PHONY: all
all: $(LIB)

$(LIB): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -shared -o $@ $^

test: $(SRCS) $(HDRS) include/cli.h
	$(CC) $(CFLAGS) $(SRCS) src/cli.c -o $(@) -lreadline

#parser: src/parser.c include/parser.h
	#$(CC) $(CFLAGS) -o parser parser.c

.PHONY: clean

clean:
	rm $(LIB) #parser

cleantest:
	rm test
