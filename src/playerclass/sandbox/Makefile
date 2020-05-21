CC = gcc
BIN = custom_skills
RM = rm -f
INCLUDE = -I ../../../include
CFLAGS = -g -O2 $(INCLUDE)
LIBPATH = ../../../build/src/
UTLIST = common/
SFLAGS = -L$(LIBPATH)$(UTLIST) -lcommon

.PHONY = all
all: 
		$(CC) $(BIN).c $(CFLAGS) $(SFLAGS) -o $(BIN) 

#$(BIN).o: $(BIN).c
#		$(CC) $(CFLAGS) $@ $(patsubst %.o, %.c, $@)

.PHONY = clean
clean:
		$(RM) $(BIN)