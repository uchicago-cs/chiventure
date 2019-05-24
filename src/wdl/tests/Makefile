#Makefile for Tests
CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../libobj/include -I../../common/include -I../../game-state/include
LDFLAGS = -L../ 
LDLIBS = ../wdl.a -lyaml -lcriterion
RM = rm -f
BIN = test-rooms

SRCS = main.c test_rooms.c
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
