#Makefile for Action Management#

#Based off Makefile template from libobj which is from https://gist.github.com/xuhdev/1873316#

CC = gcc
AR = ar
SRCS = src/actionmanagement.c src/get_actions.c 
CFLAGS = -MMD -Wall -Wextra -O0 -g -I./include/ -I../common/include/ -I../game-state/include/ -I../cli/include/ -I../ui/include/ -I../checkpointing/include -I../action-management/include -I../game-state/src
OBJS = $(SRCS:.c=.o)
LIB = action_management.a
RM = rm -f

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $@ $^ 

-include $(SRCS:.c=.d)

.PHONY: clean tests

clean:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)
	make -C ./tests clean

tests: $(LIB)
	make -C ./tests
