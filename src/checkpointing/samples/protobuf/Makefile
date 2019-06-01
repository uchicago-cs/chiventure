CC = gcc
RM = rm -f
LIBS = -lprotobuf-c


PROTO = sample.proto
COMP = sample.pb-c.c
BINS = serialize deserialize

.PHONY: all
all: $(BINS)

proto:
	protoc-c --c_out=. $(PROTO)

serialize: proto
	$(CC) -o $@ save.c $(COMP) $(LIBS)

deserialize: proto
	$(CC) -o $@ load.c $(COMP) $(LIBS)

clean:
	${RM} ${BINS} $(COMP) $(COMP:.c=.h)
