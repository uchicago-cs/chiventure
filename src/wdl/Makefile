# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../libobj/include/ -I../common/include/
RM = rm -f
LIB = wdl.a
LDLIBS = -lyaml

.PHONY: clean clean-lib clean-bin

all: $(LIB)

# Library

SRCS = src/parse.c src/validate.c
OBJS = $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

clean-lib:
	${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)

EXAMPLE_BINS = examples/typecheck_demo
EXAMPLE_SRCS=$(patsubst %, %.c, $(EXAMPLE_BINS))

$(EXAMPLE_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(EXAMPLE_SRCS:.c=.d)

$(EXAMPLE_BINS): %:%.c $(LIB)
	$(CC) $(CFLAGS) $^ -o$@ $(LDLIBS)

examples: $(EXAMPLE_BINS)

clean-bin:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d) $(EXAMPLE_SRCS:.c=.d) $(EXAMPLE_BINS)

clean: clean-lib clean-lib
