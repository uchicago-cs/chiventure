# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I ../../game-state/include
LFLAGS = -L .. -L ../../game-state
RM = rm -f
BIN = test-actionmanagement
LIBS = -l:action_management.a -l:game-state.a -lcriterion

SRCS = main.c test_get_actions.c test_action_new_init_free.c test_item_actions.c test_path_actions.c

OBJS = $(SRCS:.c=.o) 

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS) $(LIBS) 

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
