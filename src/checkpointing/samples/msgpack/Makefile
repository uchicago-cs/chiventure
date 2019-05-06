CC = gcc
CFLAGS = -Wall -g
RM = rm -f
LDLIBS = -lmsgpackc
BIN = save load

all: $(BIN)

save: save.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

load: load.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

clean:
	$(RM) $(BIN)
