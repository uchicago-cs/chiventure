CC = gcc
AR = ar
RM = rm -f 
CFLAGS = -fPIC -g -I./include
LDFLAGES = -shared
PROTOLIBS = -lprotobuf-c

PROTOCOMP = include/game.pb-c.c
PROTOFLAGS = --c_out=./include
SRCS = src/save.c src/load.c
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
