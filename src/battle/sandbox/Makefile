CC = gcc #compiler
FILEPATH = ../../task4
CFLAGS = -fPIC -Wall -Wextra -O2 -g -o 
RM = rm -f # template to clean out created files  

SRCS = main.c flow.c feedback.c enemy.c players_stats.c
BIN = sandbox

.PHONY: all clean
all: 
	$(CC) $(CFLAGS) $(BIN) $(SRCS)
clean:
	$(RM) $(BIN)
