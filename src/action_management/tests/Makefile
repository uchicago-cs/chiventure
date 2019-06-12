# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -MMD -fPIC -Wall -Wextra -O2 -g -I ../include/ -I ../../common/include/ -I ../../game-state/include -I ../../game-state/src -I ../../ui/include -I ../../cli/include -I ../../checkpointing/include
LFLAGS = -L .. -L ../../common -L ../../game-state -L ../../ui -L ../../cli -L ../../checkpointing
RM = rm -f
BIN = test-actionmanagement
LDLIBS = -lprotobuf-c -lcriterion -lncurses
LIBS = -l:common.a -l:ui.a -l:cli.a -l:action_management.a -l:game-state.a -l:checkpointing.a
SRCS = main.c test_get_actions.c test_action_new_init_free.c test_item_actions.c test_path_actions.c test_item_item_actions.c

OBJS = $(SRCS:.c=.o) 

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS) $(LIBS) $(LDLIBS)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
