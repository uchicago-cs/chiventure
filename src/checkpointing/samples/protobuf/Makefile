CC = gcc
RM = rm -f
LIBS = -lprotobuf-c

PROTO = sample.pb-c.c
BINS = serialize deserialize

.PHONY: all
all: $(BINS)

serialize:
	$(CC) -o $@ save.c $(PROTO) $(LIBS)

deserialize:
	$(CC) -o $@ load.c $(PROTO) $(LIBS)

clean:
	${RM} ${BINS}
