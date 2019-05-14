CC = gcc
CFLAGS = -fPIC -Wall -Wextra -g -O2 -lm -I../include/
STC_LDFLAGS = -L../
LIB = cli.a

SRCS = testshell.c
OBJS = $(SRCS:.c=.o)
BINS = testshell

.PHONY: all
all: $(BINS)

testshell: testshell.o ../cli.a
	$(CC) $(STC_LDFLAGS) $^ -o$@ -l:cli.a -lreadline

.PHONY: clean
clean:
	rm -f ${OBJS} ${BINS}
