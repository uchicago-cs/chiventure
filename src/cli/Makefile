
# Makefile for CS22000 Command Line Interface

CC = gcc
SRCS = src/cmd.c src/shell.c src/parser.c src/operations.c
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/ -I../game-state/include/ -I../checkpointing/include/ -I../action_management/include/ -I../ui/include/  -I../game-state/src/
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

.PHONY: clean

clean:
	${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)
	make -C ./examples clean
