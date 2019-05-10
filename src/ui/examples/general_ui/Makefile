BIN = ui
SRC = ui.c general_ui.c
HEAD = general_ui.h
LIB = -lncurses
CC = gcc
CFLAGS = -O2 -Wall -Wextra -g
RM = rm -f

.PHONY: $(BIN)

$(BIN): $(SRC) $(HEAD)
	$(CC) $(CFLAGS)  -o $@ $(SRC) $(LIB)

clean:
	$(RM) $(BIN)
