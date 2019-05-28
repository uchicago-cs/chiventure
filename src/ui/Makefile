# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/ -I../game-state/include/
RM = rm -f
LIB = ui.a
LDLIBS = -lncurses

.PHONY: all clean examples

all: $(LIB)

# Library


SRCS = src/ui.c src/window.c src/print_functions.c src/coordinate.c src/DFS.c src/map.c src/ui_ctx.c

OBJS = $(SRCS:.c=.o)
LOGS = examples/ui_debug.txt

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^


# Examples


EXAMPLE_BINS = examples/test_ui examples/map_example examples/coord_example

EXAMPLE_SRCS=$(patsubst %, %.c, $(EXAMPLE_BINS))

$(EXAMPLE_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(EXAMPLE_SRCS:.c=.d)

$(EXAMPLE_BINS): %:%.c
	$(CC) $(CFLAGS) $^ $(LIB) $(LDLIBS) -o$@

examples: $(EXAMPLE_BINS)

clean:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d) $(LOGS) $(EXAMPLE_SRCS:.c=.d) $(EXAMPLE_BINS)
