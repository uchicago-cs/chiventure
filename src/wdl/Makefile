## Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -MMD -fPIC -Wall -Wextra -O2 -g -I./include/ -I../libobj/include/ -I../game-state/include/ -I../action_management/include/ -I../common/include/ -I../ui/include -I../cli/include -I../checkpointing/include
RM = rm -f
LIB = wdl.a
LDFLAGS = -L../libobj -L../action_management
LDLIBS = ../libobj/libobj.a ../action_management/action_management.a -lyaml

.PHONY: clean clean-lib clean-bin

all: $(LIB)

# Library

SRCS = src/parse.c src/validate.c src/load_room.c src/load_item.c src/load_game.c
OBJS = $(SRCS:.c=.o)

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

clean-lib:
	${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)

# Examples

EXAMPLE_BINS = examples/typecheck_demo
EXAMPLE_SRCS=$(patsubst %, %.c, $(EXAMPLE_BINS))

-include $(EXAMPLE_SRCS:.c=.d)

$(EXAMPLE_BINS): %:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIB) $(LDLIBS) -o$@

examples: $(EXAMPLE_BINS)

clean-bin:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d) $(EXAMPLE_SRCS:.c=.d) $(EXAMPLE_BINS)

# Tests

tests: $(LIB) 
	make -C ./tests

clean-tests:
	make -C ./tests clean

clean: clean-lib clean-bin clean-tests
