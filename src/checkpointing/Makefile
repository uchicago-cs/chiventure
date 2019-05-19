CC = gcc
AR = ar
RM = rm -f 
CFLAGS = -fPIC -g -I./include
LDFLAGES = -shared
PROTOLIBS = -lprotobuf-c

PROTOCOMP = game.pb-c.c
BINS = save load
SRCS = src/save.c src/load.c
OBJS = $(SRCS:.c=.o)
STATIC_LIB = checkpointing.a


.PHONY: all
all: ${BINS} ${STATIC_LIB}

$(STATIC_LIB): $(OBJS)
	$(AR) -r -o $@ $^

game.pb-c.c: game.proto
	protoc-c --c_out=./include game.proto

save: include/game.pb-c.c src/save.c
	$(CC) -g src/save.c -I./include  $(PROTOCOMP) $(PROTOLIBS) -o src/$@

load: include/game.pb-c.c src/load.c
	$(CC) -g src/load.c -I./include $(PROTOCOMP) $(PROTOLIBS) -o src/$@

clean:
	${RM} src/*.txt src/save src/load ${PROTOCOMP} ${OBJS} ${STATIC_LIB} ${PROTOCOMP:.c=.h}
