CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
RM = rm -f
SRCS = game.c
OBJS = $(SRCS:.c=.o)
LIBS = $(SRCS:.c=.so)
BINS = $(SRCS:.c=)

.PHONY all
all: $(OBJS)

$(OBJS): $(SRCS)

.PHONY clean
clean:
	$(RM) $(LIBS) $(OBJS) $(BINS)
