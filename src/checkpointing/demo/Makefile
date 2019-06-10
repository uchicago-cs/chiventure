# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../game-state/include -I../../game-state/src -I../../common/include -I../../action_management/include/
RM = rm -f
SAVE = demo-save
LOAD = demo-load
LDLIBS = -lprotobuf-c -lcriterion
COMMON = -L../../common/ -Wl,-rpath,../../common/ -l:common.a
GAME_STATE = -L../../game-state/ -Wl,-rpath,../../game-state/ -l:game-state.a
ACTION_MANAGEMENT = -L../../action_management/ -Wl,-rpath,../../action_management/ -l:action_management.a
CHECKPOINTING = -L../ -Wl,-rpath,../ -l:checkpointing.a
STLIBS = $(COMMON) $(GAME_STATE) $(CHECKPOINTING) $(ACTION_MANAGEMENT)

SAVE_SRCS = demo_save.c
LOAD_SRCS = demo_load.c
SAVE_OBJS = $(SAVE_SRCS:.c=.o)
LOAD_OBJS = $(LOAD_SRCS:.c=.o)

.PHONY: all
all: ${SAVE} ${LOAD}

$(SAVE): $(SAVE_OBJS)
	$(CC) $(SAVE_OBJS) $(STLIBS) -o $(SAVE) $(LDLIBS)

$(LOAD): $(LOAD_OBJS)
	$(CC) $(LOAD_OBJS) $(STLIBS) -o $(LOAD) $(LDLIBS)

$(SAVE_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(LOAD_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SAVE_SRCS:.c=.d)

include $(LOAD_SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${SAVE} ${LOAD} ${LOAD_OBJS} ${SAVE_OBJS} $(LOAD_SRCS:.c=.d) $(SAVE_SRCS:.c=.d)
