## Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../libobj/include/ -I../common/include/ -I../game-state/include/ -I../action_management/include/
RM = rm -f
LIB = wdl.a
LDFLAGS = -L../libobj -L../action_management
LDLIBS = ../libobj/libobj.a ../action_management/action_management.a -lyaml


.PHONY: clean clean-lib clean-bin

all: $(LIB)

# Library

SRCS = src/parse.c src/validate.c src/load_room.c src/load_item.c src/load_game.c src/load_wdl.c
OBJS = $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

clean-lib:
	${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)

# Examples

EXAMPLE_BINS = examples/typecheck_demo
EXAMPLE_SRCS=$(patsubst %, %.c, $(EXAMPLE_BINS))

$(EXAMPLE_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

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
