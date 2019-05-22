# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/
RM = rm -f
LIB = ui.a
LDLIBS =  -lncurses

.PHONY: all clean examples

all: $(LIB)

# Library

SRCS = src/ui.c src/window.c src/print_functions.c src/map.c # src/coordinate.c src/DFS.c
OBJS = $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^


# Examples

EXAMPLE_BINS = examples/test_ui examples/map_example #examples/coord_example
EXAMPLE_SRCS=$(patsubst %, %.c, $(EXAMPLE_BINS))

$(EXAMPLE_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(EXAMPLE_SRCS:.c=.d)

$(EXAMPLE_BINS): %:%.c $(LIB)
	$(CC) $(CFLAGS) $^ -o$@ $(LDLIBS)

examples: $(EXAMPLE_BINS)

clean:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d) $(EXAMPLE_SRCS:.c=.d) $(EXAMPLE_BINS)
