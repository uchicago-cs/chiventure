#Makefile for Tests
CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../../game-state/include/ -I../include/ -I../../action_management/include/ -I../../libobj/include -I../../common/include
LDFLAGS = -L../ -L../../libobj -L../../game-state
LDLIBS = ../wdl.a ../../libobj/libobj.a ../../game-state/game-state.a -lyaml -lcriterion
RM = rm -f
BIN = test-wdl

SRCS = main.c test_room.c test_item.c
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
