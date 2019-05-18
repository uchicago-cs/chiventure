CC = gcc
AR = ar
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I../common/include/ -I./src/
RM = rm -f
SRCDIR = src
DEPDIR = dep
BUILDDIR = build
SRCEXT = c
SRCS = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
DEPS = $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SOURCES:.$(SRCEXT)=.d))
OBJS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
BINS = $(SRCS:.c=)
LIB = game-state.a

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	$(AR) -r -o $@ $^

$(DEPDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	mkdir -p $(DEPDIR)
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(DEPS)

# Alias
$(patsubst $(SRCDIR)/%.c, %, $(SRCS)): $(patsubst %, $(DEPDIR)/%.d, $<) 

.PHONY: clean
clean:
	$(RM) $(LIB) $(OBJS) $(BINS)
