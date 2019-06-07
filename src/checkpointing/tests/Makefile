# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g  -I../include/ -I../../game-state/include -I../../common/include -I../../action_management/include/
RM = rm -f
BIN = test-checkpointing
LDLIBS = -lprotobuf-c -lcriterion
COMMON = -L../../common/ -Wl,-rpath,../../common/ -l:common.a
GAME_STATE = -L../../game-state/ -Wl,-rpath,../../game-state/ -l:game-state.a
ACTION_MANAGEMENT = -L../../action_management/ -Wl,-rpath,../../action_management/ -l:action_management.a
CHECKPOINTING = -L../ -Wl,-rpath,../ -l:checkpointing.a
STLIBS = $(COMMON) $(GAME_STATE) $(CHECKPOINTING) $(ACTION_MANAGEMENT)

SRCS = main.c test_load.c test_save.c
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
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
