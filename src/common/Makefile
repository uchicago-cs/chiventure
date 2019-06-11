# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -MMD -fPIC -Wall -Wextra -O2 -g -I./include/ -I../game-state/include/ -I../ui/include/ -I../cli/include/ -I../action_management/include/
RM = rm -f
LIB = common.a

.PHONY: all clean

all: $(LIB)

# Library

SRCS = src/ctx.c src/sample_game.c 
OBJS = $(SRCS:.c=.o)

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

clean:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)
