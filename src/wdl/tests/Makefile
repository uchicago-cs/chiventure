#Makefile for Tests
CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../../game-state/include/ -I../include/ -I../../action_management/include/ -I../../libobj/include -I../../common/include
LDFLAGS = -L../ -L../../libobj -L../../game-state -L../../action_management
LDLIBS = ../wdl.a ../../libobj/libobj.a ../../game-state/game-state.a ../../action_management/action_management.a -lyaml -lcriterion
RM = rm -f
BIN = test-wdl

SRCS = main.c test_room.c test_item.c test_game.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o$(BIN) $(LDLIBS) 

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
