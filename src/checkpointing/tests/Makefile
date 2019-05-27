CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
LDFLAGS = -L../ -W1,-rpath,.
RM = rm-f
BIN = test-checkpointing
LDLIBS = -lcriterion -checkpointing

SRC = test_save.c
OBJS = $(SRC:.c=.o)

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)

$(SRC:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
