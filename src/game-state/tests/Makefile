CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/ -I../../common/include/ -I../src/
LDFLAGS = -L../ -Wl,-rpath,.
LDLIBS = -lcriterion -l:libgamestate.a
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
