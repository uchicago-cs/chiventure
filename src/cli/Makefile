# Makefile for CS22000 Command Line Interface
 

CC = gcc
BINS = cli
SRCS = src/cmd.c src/shell.c src/cli.c src/parser.c 
HDRS = include/cmd.h include/cli.h include/shell.h include/parser.h
CFLAGS = -fPIC -Wall -Wextra -g -O2 -lm -I./include/ -I../common/include/
OBJS = $(SRCS:.c=.o)
LIB = cli.so

.PHONY: all
all: $(LIB)

$(LIB): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -shared -o $@ $^

test: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS) -o $(@) -lreadline

#parser: src/parser.c include/parser.h 
	#$(CC) $(CFLAGS) -o parser parser.c

.PHONY: clean
# type 'make clean' to remove the executable and debug information
clean:
	rm $(BINS) $(LIB) $(OBJS) test parser
