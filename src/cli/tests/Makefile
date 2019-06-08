CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/
LIBS = -lcriterion
RM = rm -f
SRCS = main.c test_parser.c
OBJS = $(SRCS:.c=.o)
BIN = test-cli

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o$(BIN)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)