BIN = ncurses_ui
SRC = ncurses_ui.c
LIB = -lncurses
CC = gcc
CFLAGS = -O2 -Wall -Wextra -g 
RM = rm -f

.PHONY: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS)  -o $@ $(SRC) $(LIB)

clean:
	$(RM) $(BIN)
