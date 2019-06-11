CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../cli/include/ -I../../game-state/include/ -I../../action_management/include/ -I../../ui/include

RM = rm -f
LDLIBS = -lreadline -lncursesw

COMMON = -L../ -Wl,-rpath,../ -l:common.a
GAME_STATE = -L../../game-state/ -Wl,-rpath,../../game-state/ -l:game-state.a
ACTION_MANAGEMENT = -L../../action_management/  -Wl,-rpath,../../action_management/ -l:action_management.a
CLI = -L../../cli -Wl,-rpath,../../cli -l:cli.a
UI = -L../../ui/ -Wl,-rpath,../../ui/ -l:ui.a

STLIBS = $(COMMON) $(UI) $(CLI) $(GAME_STATE) $(ACTION_MANAGEMENT) -L /lib64
SRCS = example_game.c
OBJS = $(SRCS:.c=.o)
BIN = example_game

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) $(STLIBS) -o$(BIN)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
