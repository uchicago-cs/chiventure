CC = gcc
AR = ar
RM = rm -f 
CFLAGS = -fPIC -g -I./include -I../common/include -I../game-state/include
LDFLAGES = -shared
PROTOLIBS = -lprotobuf-c

COMMON = -L../../common/ -Wl,-rpath,../../common/ -l:common.a
GAME_STATE = -L../../game-state/ -Wl,-rpath,../../game-state/ -l:game-state.a
CHECKPOINTING = -L../ -Wl,-rpath,../ -l:checkpointing.a
STLIBS = $(COMMON) $(GAME_STATE) $(CHECKPOINTING)

PROTOHD = include/game.pb-c.h
PROTOCOMP = src/game.pb-c.c
PROTOFLAGS = --c_out=./src
SRCS = src/game.pb-c.c src/save.c src/load.c
OBJS = $(SRCS:.c=.o)
STATIC_LIB = checkpointing.a

.PHONY: all

all: $(PROTOCOMP) $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(AR) -r -o $@ $^

$(PROTOCOMP): game.proto
	protoc-c $(PROTOFLAGS) $^
	mv src/game.pb-c.h include/

clean:
	$(RM) $(PROTOHD) $(PROTOCOMP) $(OBJS) $(STATIC_LIB)

tests: ${STATIC_LIB}
	make -C ./tests
