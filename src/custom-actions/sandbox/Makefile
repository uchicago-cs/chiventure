CC = gcc
FLAGS = -w
INCLUDE = -I ../../../include/ -I ../include/
SRC = ../../game-state/src/path.c  ../src/interface.c ../../game-state/src/game.c ../../game-state/src/player.c ../../game-state/src/room.c ../../game-state/src/game_action.c ../../game-state/src/item.c
FILE = sandbox.c

.PHONY: all, clean

all:
	$(CC) $(INCLUDE) $(SRC) $(FILE) -o sandbox
