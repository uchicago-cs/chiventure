# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I./src/common/include -I./src/game-state/include -I./src/ui/include
RM = rm -f
LDLIBS = -lyaml -lncurses
BIN = chiventure

.PHONY: all clean libs

all: $(BIN)

# Rules for making components
# Each component must have a directory inside src/
# The component directory must have a Makefile that
# generates a static library file with the same
# name as a component. For example, for the cli
# component:
#
#  - Directory: src/ui/
#  - Makefile: src/ui/Makefile
#  - Library: src/ui/ui.a

COMPONENTS = libobj common ui cli game-state action_management checkpointing
LIBS = $(foreach comp,$(COMPONENTS),src/$(comp)/$(comp).a)

$(LIBS):
	make -C ./src/$(basename $(notdir $@))/


# Rules for making the chiventure executable

SRCS = src/chiventure.c
OBJS = $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(BIN): $(OBJS) $(LIBS)
	$(CC) $^ -o$@ $(LDLIBS)

clean:
	-${RM} ${OBJS} $(SRCS:.c=.d)
	-for COMP in $(COMPONENTS); do make -C src/$$COMP/ clean; done
