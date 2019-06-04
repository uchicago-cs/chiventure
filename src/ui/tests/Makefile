CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I.../include/
LDFLAGS = -L../ -Wl,-rpath,../
RM = rm -f
BIN = test-coordinates
LDLIBS = -lcriterion

SRCS = ../src/coordinate.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o$(BIN) $(LDLIBS)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${BIN} 
