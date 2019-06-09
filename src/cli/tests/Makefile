CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../../game-state/include/ -I../../action_management/include/ -I../../ui/include/
RM = rm -f
LDLIBS = -lcriterion 

COMMON = -L../../common/ 
GAME_STATE = -L../../game-state/ 
ACTION_MANAGEMENT = -L../../action_management/ 
CLI = -L../ 
UI = -L../../ui/ 

STLIBS = $(COMMON) $(UI) $(CLI) $(GAME_STATE) $(ACTION_MANAGEMENT) -Wl,--start-group -lncurses -l:cli.a -l:ui.a -l:game-state.a -l:action_management.a -Wl,--end-group  

SRCS = main.c test_parser.c
OBJS = $(SRCS:.c=.o)
BIN = test_cli

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) $(STLIBS) -o$(BIN)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)

