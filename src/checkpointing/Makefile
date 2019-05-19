CC = gcc
AR = ar
RM = rm -f 
CFLAGS = -fPIC -g -I./include
LDFLAGES = -shared
PROTOLIBS = -lprotobuf-c

PROTOCOMP =include/game.pb-c.c
BINS = save load
SRCS = src/save.c src/load.c
OBJS = $(SRCS:.c=.o)
STATIC_LIB = checkpointing.a


.PHONY: all
all:$(PROTOCOMP) ${STATIC_LIB}

$(STATIC_LIB): $(OBJS)
	$(AR) -r -o $@ $^

$(PROTOCOMP): game.proto
	protoc-c --c_out=./include game.proto

save: $(PROTOCOMP) src/save.c
	$(CC) -g src/save.c -I./include $(PROTOCOMP) $(PROTOLIBS) -o save

load: $(PROTOCOMP) src/load.c
	$(CC) -g src/load.c -I./include $(PROTOCOMP) $(PROTOLIBS) -o load

clean:
	${RM} src/*.txt src/save src/load ${PROTOCOMP} ${OBJS} ${STATIC_LIB} ${PROTOCOMP:.c=.h}
