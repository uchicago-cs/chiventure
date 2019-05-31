CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../../game-state/include/ -I../../action_management/include/ -I../../ui/include/
RM = rm -f
LDLIBS = -lreadline 

COMMON = -L../common/ -Wl,-rpath,../common/ -l:common.a
CLI = -L../ -WL,-rpath,../ -l:cli.a
AM = -L../action_management/ -Wl,-rpath,../action_management/ -l:action_management.a
UI = -L../ui/ -Wl,-rpath,../ui/ -l:ui.a
STLIBS = $(COMMON) $(UI) $(CLI) $(AM)

SRCS = testshell.c
OBJS = $(SRCS:.c=.o)
BIN = testshell

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(STLIBS) $(CFLAGS) $(OBJS) $(LDLIBS) -o$(BIN)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)

