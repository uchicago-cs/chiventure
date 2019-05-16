# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../libobj/include/ -I../common/include/
RM = rm -f
LIB = wdl.a
LDLIBS = -lyaml

.PHONY: all clean examples

all: $(LIB)

# Library

SRCS = src/parse.c src/validate.c
OBJS = $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

clean:
	${RM} ${LIB} ${OBJS} $(SRCS:.c=.d)