CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../../game-state/include/ -I../../action_management/include/
LDFLAGS = -L../ -Wl,-rpath,.
RM = rm -f

SRCS = testshell.c
OBJS = $(SRCS:.c=.o)
BIN = testshell

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) -o$(BIN) -l:cli.a -lreadline

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)

