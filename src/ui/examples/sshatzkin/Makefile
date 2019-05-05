.PHONY:
LDFLAGS = -lncurses
CFLAGS = -W -Wall -Wextra
CC = gcc
SRCS = demo.c split_demo.c demo2.c
BINS = $(SRCS:.c=)
#CLEAN = rm -f $@

all: demo

$(BINS): $(CLEAN)
	$(CC) $(CFLAGS) $(patsubst %,%.c,$@) -o $@ $(LDFLAGS)

#$(SRCS):
#	rm -f $(patsubst %.c,%,$@)

#demo: demo.c
#	$(CC) $(CFLAGS) demo.c -o demo $(LDFLAGS)

#split: #split_demo.c
#	$(CC) $(CFLAGS) split_demo.c -o split $(LDFLAGS)
