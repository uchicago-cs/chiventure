CC = gcc
CFLAGS = -I../../include/game-state -fPIC -g -O2 -Wall -Wextra

SRCS = read_gdl.c
OBJS = $(SRCS:.c=.o)

BINS = read_gdl

all: $(BINS)

.PHONY: clean all

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(BINS): $(OBJS)
	$(CC) $(OBJS) -o $@

clean:
	rm -f $(OBJS) $(BINS)
