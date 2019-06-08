CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../../game-state/include/ -I../../action_management/include/
LDFLAGS = -L../ -L../../action_management/ -Wl,-rpath,../ -Wl,-rpath,../../action_management/
RM = rm -f
LDLIBS = -lreadline 

SRCS = testshell.c
OBJS = $(SRCS:.c=.o)
BIN = testshell

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) $(LDLIBS) -o$(BIN) -l:cli.a -l:action_management.a

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)

