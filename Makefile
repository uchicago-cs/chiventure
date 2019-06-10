# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I./src/checkpointing/include -I./src/common/include -I./src/game-state/include -I./src/ui/include -I./src/cli/include -I./src/action_management/include -I./src/game-state/src
RM = rm -f
LDLIBS = -lyaml -lncurses -lreadline -lprotobuf-c
BIN = chiventure

.PHONY: proto all clean

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

COMPONENTS = libobj common ui cli checkpointing game-state action_management wdl

LIBS = $(foreach comp,$(COMPONENTS),src/$(comp)/$(comp).a)

$(LIBS):
	make -C ./src/checkpointing
	make -C ./src/$(basename $(notdir $@))/


# Rules for making the chiventure executable

SRCS = src/chiventure.c
OBJS = $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c $(LIBS)
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

$(BIN): $(OBJS) $(LIBS)
	$(CC) $^ -o $@ $(LDLIBS)

clean:
	-${RM} ${OBJS} $(SRCS:.c=.d)
	-for COMP in $(COMPONENTS); do make -C src/$$COMP/ clean; done

