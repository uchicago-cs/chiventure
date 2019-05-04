# Makefile for using library and connecting our files
# compiler
CC = gcc
# compiler flags
CFLAGS = -I./include/ -I../libobj/include/ -I../common/include/ -O2 -Wall -Wextra -g -fPIC
# remove command
RM = rm -f
# library flags
LDFLAGS = -L../libobj/ -Wl,-rpath=../libobj/
# library name
LIB = -lobj
# sources
SRCS = src/main.c
# objects
OBJ = $(SRCS:.c=.o)
# bin
BIN = main

.PHONY = all
all: $(BIN)

main.o: $(SRCS)

main: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIB) -o $@

.PHONY = clean

clean:
	$(RM) $(BIN) $(OBJ)
