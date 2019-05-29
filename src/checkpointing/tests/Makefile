# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g  -I../include/ -I../../game-state/include -I../../common/include
LDFLAGS = -L../ -Wl,-rpath,. -L../../game-state/ -Wl,-rpath,.
RM = rm -f
BIN = test-checkpointing
LDLIBS = -lcriterion -lcheckpointing -lgame-state

SRCS = main.c test_save.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LDFLAGS) $(LDLIBS) 

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
