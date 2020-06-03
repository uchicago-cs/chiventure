.PHONY: clean all
BIN = wdlparser
SRCS = wdlparser.c
OBJS = wdlparser.o

CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -fPIC -c -I /usr/include/
RM = rm -f
DYN_LDFLAGS = -L /usr/lib/x86_64-linux-gnu/ -Wl,-rpath=/usr/lib/x86_64-linux-gnu/
LDLIBS = -ljson-c -lzip
LD_LIBRARY_PATH = /usr/lib/x86_64-linux-gnu/


$(BIN): wdlparser.o
		$(CC) $(DYN_LDFAGS) $^ -o $@ $(LDLIBS)

$(OBJS): %.o:%.c
		$(CC) $(CFLAGS) -o $@ $(patsubst %.o, %.c, $@)
