CC = gcc
BIN = player
RM = rm -f
INCLUDE = -I ../../../include
CFLAGS = -g -O2 $(INCLUDE)
LIBPATH = ../../../build/src/
LIBOBJ = libobj/
UTLIST = common/
GAMESTATE = game-state/
SFLAGS = -L$(LIBPATH)$(LIBOBJ) -llibobj -L$(LIBPATH)$(UTLIST) -lcommon -L$(LIBPATH)$(GAMESTATE) -lgame-state

.PHONY = all
all:
		$(CC) $(BIN).c $(CFLAGS) $(SFLAGS) -o $(BIN)

#$(BIN).o: $(BIN).c
#		$(CC) $(CFLAGS) $@ $(patsubst %.o, %.c, $@)

.PHONY = clean
clean:
		$(RM) $(BIN)
