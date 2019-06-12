# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include -I../../game-state/include -I../../game-state/src -I../../action_management/include/ -I../../ui/include/ -I../../cli/include/
RM = rm -f
BIN = demo-checkpointing
LDLIBS = -lprotobuf-c
COMMON = -L../../common/ -Wl,-rpath,../../common/ -l:common.a
GAME_STATE = -L../../game-state/ -Wl,-rpath,../../game-state/ -l:game-state.a
ACTION_MANAGEMENT = -L../../action_management/ -Wl,-rpath,../../action_management/ -l:action_management.a
CHECKPOINTING = -L../ -Wl,-rpath,../ -l:checkpointing.a
STLIBS = $(COMMON) $(GAME_STATE) $(CHECKPOINTING) $(ACTION_MANAGEMENT)

SRCS = demo.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(STLIBS) -o $(BIN) $(LDLIBS)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d) *.txt
