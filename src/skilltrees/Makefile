CC = gcc
CFLAGS = -O2 -Wall -Wextra -g -fPIC -I ../../include/skilltrees/
LDFLAGS = -shared
RM = rm -f
LIB = libskilltrees.so

SRCS = skilltrees.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(OBJS)
	$(CC) $(LDFLAGS) -o $(LIB) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $(patsubst %.o, %.c, $@)

clean:
	$(RM) $(LIB) $(OBJS)
