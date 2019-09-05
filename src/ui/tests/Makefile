CC = gcc
CFLAGS = -MMD -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../../game-state/include/ -I../../cli/include/ -I../../action_management/include/
UI = -L../. -Wl,-rpath,../.
COMMON = -L../../common/ -Wl,-rpath,../../common/ -l:common.a
CLI = -L../../cli/ -Wl,-rpath,../../cli/ -l:cli.a
GAME_STATE = -L../../game-state/ -Wl,-rpath,../../game-state/ -l:game-state.a
STLIBS = $(UI) $(COMMON) $(CLI) $(GAME_STATE)

RM = rm -f
BIN = test-coordinates
LDLIBS = -lcriterion -l:ui.a

SRCS = main.c test_coordinate.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o$(BIN) $(STLIBS) $(LDLIBS)

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
