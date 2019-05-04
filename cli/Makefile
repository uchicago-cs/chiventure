# Makefile for CS22000 Command Line Interface
 
CC = clang
BINS = cli
SRCS = cmd.c shell.c cli.c 
HDRS = cmd.h cli.h shell.h
CFLAGS = -Wall -Wextra -g -lm 

.PHONY: clean

$(BINS): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS) -o $(@) -lreadline

# type 'make clean' to remove the executable and debug information
clean:
	rm $(BINS)
