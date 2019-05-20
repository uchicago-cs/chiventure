CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/ -I./src/
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
RM = rm -f
SRCDIR = src
DEPDIR = .dep
BUILDDIR = build
$(shell mkdir -p $(DEPDIR) >/dev/null)
$(shell mkdir -p $(BUILDDIR) >/dev/null)
SRCEXT = c
SRCS = $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
DEPS = $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.$(SRCEXT)=.d))
OBJS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.o))
LIB = game-state.a

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPDIR)/%.d
	$(CC) $(CFLAGS) $(DEPFLAGS) $< -c -o $@

$(DEPDIR)/%.d: ;

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(LIB) $(OBJS) $(BINS)
	make -C tests/ clean

.PHONY: cleanall
cleanall:
	$(RM) $(LIB) $(OBJS) $(BINS) $(DEPS)
	make -C tests/ clean

.PHONY: tests
tests:
	make all
	make -C tests/ all

