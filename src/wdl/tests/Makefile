#Makefile for Tests
CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
LDFLAGS = 
RM = rm -f
BIN = test-rooms
LDLIBS = -lcriterion

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
