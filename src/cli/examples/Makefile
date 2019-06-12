CC = gcc
CFLAGS = -MMD -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../../game-state/include/ -I../../game-state/src -I../../action_management/include/ -I../../ui/include -I../../checkpointing/include

RM = rm -f
LDLIBS = -lreadline 

COMMON = -L../../common/ -Wl,-rpath,../../common/ -l:common.a
GAME_STATE = -L../../game-state/ -Wl,-rpath,../../game-state/ -l:game-state.a
ACTION_MANAGEMENT = -L../../action_management/  -Wl,-rpath,../../action_management/ -l:action_management.a
CLI = -L../ -Wl,-rpath,../ -l:cli.a
UI = -L../../ui/ -Wl,-rpath,../../ui/ -l:ui.a
CHECKPOINTING = -L../../checkpointing -Wl,-rpath,../../checkpointing -l:checkpointing.a

STLIBS = $(COMMON) $(UI) $(CLI) $(GAME_STATE) $(ACTION_MANAGEMENT) $(CHECKPOINTING)
SRCS = testshell.c
OBJS = $(SRCS:.c=.o)
BIN = testshell

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) $(STLIBS) -o$(BIN)

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
