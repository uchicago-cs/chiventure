CC = gcc
CFLAGS = -I../../include/ -fPIC -g -O2 -Wall -Wextra
LDFLAGS = -L../
LDLIBS = -lcriterion


SRCS = read_gdl.c test_dimensions.c test_camera.c
OBJS = $(SRCS:.c=.o)

BINS = read_gdl test

all: $(BINS)

.PHONY: clean all

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(BINS): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJS) $(BINS)
