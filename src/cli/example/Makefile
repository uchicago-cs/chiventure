CC = gcc
STC_LDFLAGS = -L../
LIB = cli.a
RM = rm -f

SRCS = testshell.c
OBJS = $(SRCS:.c=.o)
BINS = testshell

.PHONY: all
all: $(BINS)

testshell: testshell.o ../cli.a 
	$(CC) $(STC_LDFLAGS) $^ -o$@ -l:cli.a -lreadline

.PHONY: clean
clean:
	$(RM) ${OBJS} ${BINS}
