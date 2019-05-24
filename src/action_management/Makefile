#Makefile for Action Management#

#Based off Makefile template from libobj which is from https://gist.github.com/xuhdev/1873316#

CC = gcc
SRCS = src/actionmanagement.c src/game.c src/get_actions.c
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/ -I ../game-state/include/
LDFLAGS = -shared
OBJS = $(SRCS:.c=.o)
LIB = action_management.a
RM = rm -f

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

.PHONY: clean

clean:
	${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)