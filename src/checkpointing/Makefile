CC = gcc
AR = ar
RM = rm -f 
CFLAGS = -fPIC -g -I./include -I../common/include -I../game-state/include
LDFLAGES = -shared
PROTOLIBS = -lprotobuf-c

PROTOCOMP = include/game.pb-c.c
PROTOFLAGS = --c_out=./include
SRCS = src/save.c
OBJS = $(SRCS:.c=.o)
STATIC_LIB = checkpointing.a


.PHONY: all

all: $(PROTOCOMP) $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(AR) -r -o $@ $^

$(PROTOCOMP): game.proto
	protoc-c $(PROTOFLAGS) $^

clean:
	$(RM) $(PROTOCOMP) $(OBJS) $(STATIC_LIB) $(PROTOCOMP:.c=.h)

tests: ${STATIC_LIB}
	make -C ./tests
