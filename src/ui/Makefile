# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -MMD -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/ -I../game-state/include/ -I../cli/include/ -I../action_management/include/ -I../checkpointing/include -I../game-state/src
RM = rm -f
LIB = ui.a
LDLIBS = -lncursesw -lreadline

CHECKPOINTING = -L../checkpointing -Wl,-rpath,../checkpointing -l:checkpointing.a
COMMON = -L../common/ -Wl,-rpath,../common/ -l:common.a
CLI = -L../cli/ -Wl,-rpath,../cli/ -l:cli.a
GAME_STATE = -L../game-state/ -Wl,-rpath,../game-state/ -l:game-state.a
AM = -L../action_management/ -Wl,-rpath,../action_management/ -l:action_management.a
STLIBS = $(COMMON) $(CLI) $(GAME_STATE) $(AM)

.PHONY: all clean examples

all: $(LIB)

# Library


SRCS = src/ui.c src/window.c src/print_functions.c src/coordinate.c src/DFS.c src/map.c src/ui_ctx.c

OBJS = $(SRCS:.c=.o)
LOGS = examples/ui_debug.txt

-include $(SRCS:.c=.d)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^


# Examples

#LIB2 =  ../common/common.a ui.a ../game-state/game-state.a

EXAMPLE_BINS = examples/map_example examples/coord_example examples/test_ui

EXAMPLE_SRCS=$(patsubst %, %.c, $(EXAMPLE_BINS))

-include $(EXAMPLE_SRCS:.c=.d)

$(EXAMPLE_BINS): %:%.c $(LIB)
	$(CC) $(CFLAGS) $^ $(STLIBS) -o$@ $(LDLIBS)

examples: $(EXAMPLE_BINS)

clean:
	-${RM} ${LIB} ${OBJS} $(SRCS:.c=.d) $(LOGS) $(EXAMPLE_SRCS:.c=.d) $(EXAMPLE_BINS)
