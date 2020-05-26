CC = gcc
FLAGS = -w
INCLUDE = -I ..\..\..\include -I ..\include
SRC = ..\src\interface.c ..\..\game-state\src\game.c ..\..\game-state\src\player.c 
FILE = ..\..\..\include\custom-actions\sandbox\sandbox.c

.PHONY: all, clean

all:
	$(CC) $(INCLUDE) $(SRC) $(FILE) -o sandbox