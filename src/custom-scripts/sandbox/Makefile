CC = gcc

SRCS = dark_room.c gold.c
OBJS = $(SRCS:.c=.o)

.PHONY: clean all

$(OBJS): %.o:%.c
	$(CC) $< -c -o $@

$(LIB): $(OBJS)
	$(CC) -shared -o $@ $^

$(BINS): %:src/tools/%.c $(LIB)
	$(CC) $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJS) $(LIB) $(BINS)