# Makefile for using library and connecting our files
# compiler
CC = gcc
# compiler flags
CFLAGS = -I./include/ -I../libobj/include/ -I../common/include/ -O2 -Wall -Wextra -g -fPIC
# remove command
RM = rm -f
# library flags
LDFLAGS = -L../libobj/ -Wl,-rpath=../libobj/
# libraries
LIB = -lobj
LDLIBS = -lyaml
# sources
SRCS = src/main.c src/parse.c src/validate.c
# objects
OBJ = $(SRCS:.c=.o)
# bin
BIN = main

.PHONY = all
all: $(BIN)

main.o: $(SRCS)

main: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIB) $(LDLIBS) -o $@

.PHONY = clean

clean:
	$(RM) $(BIN) $(OBJ)
