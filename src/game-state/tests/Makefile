CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../src/ -I../../action_management/include
LDFLAGS = -L../ -Wl,-rpath,.
LDLIBS = -lcriterion -l:game-state.a
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
RM = rm -f
SRCDIR = .
DEPDIR = .dep
BUILDDIR = .
$(shell mkdir -p $(DEPDIR) >/dev/null)
$(shell mkdir -p $(BUILDDIR) >/dev/null)
SRCEXT = c
SRCS = $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
DEPS = $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.$(SRCEXT)=.d))
OBJS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.o))
BIN = test-libgamestate

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPDIR)/%.d
	$(CC) $(CFLAGS) $(DEPFLAGS) $< -c -o $@

$(DEPDIR)/%.d: ;

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(BIN) $(OBJS) $(BINS) $(DEPS)





# CC = gcc
# CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ ../common/include/
# LDFLAGS = -L../ -Wl,-rpath,.
# RM = rm -f
# BIN = test-libgamestate
# LDLIBS = -lcriterion
#
# SRCS = main.c test_game.c test_players.c test_path.c test_rooms.c test_items.c
# OBJS = $(SRCS:.c=.o)
#
# .PHONY: all
# all: ${BIN}
#
# $(BIN): $(OBJS)
# 	$(CC) $(LDFLAGS) $(OBJS) -o$(BIN) $(LDLIBS)
#
# $(SRCS:.c=.d):%.d:%.c
# 	$(CC) $(CFLAGS) -MM $< >$@
#
# include $(SRCS:.c=.d)
#
# .PHONY: clean
# clean:
# 	-${RM} ${BIN} ${OBJS} $(SRCS:.c=.d)
