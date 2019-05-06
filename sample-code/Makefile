CC = gcc
CFLAGS = -Wall -g
RM = rm -f
LDLIBS = -lmsgpackc
BIN = write read

all: $(BIN)

write: write.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

read: read.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

clean:
	$(RM) $(BIN)
