CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/
RM = rm -f
SRCS = src/game.c src/player.c src/item.c src/room.c
OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)
LIB = gamestate.so

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $^

$(OBJS): $(SRCS)

.PHONY: clean
clean:
	$(RM) $(LIB) $(OBJS) $(BINS)
