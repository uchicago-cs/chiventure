CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/ -I./src/
RM = rm -f
SRCDIR = src
DEPDIR = .dep
$(shell mkdir -p $(DEPDIR) >/dev/null)
BUILDDIR = build
$(shell mkdir -p $(BUILDDIR) >/dev/null)
SRCEXT = c
SRCS = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
DEPS = $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.$(SRCEXT)=.d))
OBJS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.o))
BINS = $(SRCS:.c=)
LIB = game-state.a
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

# $(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPDIR)/%.d
	$(CC) $(CFLAGS) $(DEPFLAGS) $< -c -o $@

$(DEPDIR)/%.d: ;

-include $(DEPS)

# Alias
$(patsubst $(SRCDIR)/%.c, %, $(SRCS)): $(patsubst %, $(DEPDIR)/%.d, $<) 

.PHONY: clean
clean:
	$(RM) $(LIB) $(OBJS) $(BINS) $(DEPS)
