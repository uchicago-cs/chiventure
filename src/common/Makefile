# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../game-state/include/ -I../ui/include/ -I../cli/include/ -I../action_management/include/ -I../checkpointing/include/ -I../game-state/src
RM = rm -f
LIB = common.a

.PHONY: all clean

all: $(LIB)

# Library

SRCS = src/ctx.c src/sample_game.c 
OBJS = $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

clean:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)
