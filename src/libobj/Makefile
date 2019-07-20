# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar 
CFLAGS = -MMD -fPIC -Wall -Wextra -O0 -g -I./include/ -I../common/include/
RM = rm -f
LIB = libobj.a
LDLIBS = -lyaml

.PHONY: all clean examples

all: $(LIB)

# Library

SRCS = src/obj.c src/parser.c src/stack.c
OBJS = $(SRCS:.c=.o)

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^


# Examples

EXAMPLE_BINS = examples/obj examples/parse
EXAMPLE_SRCS=$(patsubst %, %.c, $(EXAMPLE_BINS))

-include $(EXAMPLE_SRCS:.c=.d)

$(EXAMPLE_BINS): %:%.c $(LIB)
	$(CC) $(CFLAGS) $^ -o$@ $(LDLIBS)

examples: $(EXAMPLE_BINS)

clean:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d) $(EXAMPLE_SRCS:.c=.d) $(EXAMPLE_BINS)

