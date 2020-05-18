.PHONY: clean all
BIN = parsetojsonobj
SRCS = parsetojsonobj.c
OBJS = parsetojsonobj.c

CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -fPIC -c -I.../lib
RM = rm -f
DYN_LDFLAGS = -L /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64 -Wl,-rpath=/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64 
LDLIBS = -lzip
LD_LIBRARY_PATH = /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64


$(BIN): parsetojsonobj.o 
	$(CC) $(DYN_LDFAGS) $^ -o $@ $(LDLIBS)

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o, %.c, $@)

clean:
	$(RM) ${OBJS} $(BIN)