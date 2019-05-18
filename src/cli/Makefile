# Makefile for CS22000 Command Line Interface

CC = gcc
SRCS = src/cmd.c src/shell.c src/parser.c src/operations.c src/validate.c src/lookup.c
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/
OBJS = $(SRCS:.c=.o)
LIB = cli.a
RM = rm -f

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	ar -r -o $@ $(OBJS)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

test: $(LIB)
	make -C ./example

.PHONY: clean

clean:
	${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)
	make -C ./example clean
