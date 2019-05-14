# Makefile for CS22000 Command Line Interface

CC = gcc
SRCS = src/cmd.c src/shell.c src/parser.c src/operations.c src/validate.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -fPIC -Wall -Wextra -g -O2 -lm -I./include/ -I../common/include/
LIB = cli.a

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	ar -r -o $@ $^ 

test: $(LIB)	
	make -C ./example

.PHONY: clean

clean:
	rm -f $(LIB)
	make -C ./example clean
