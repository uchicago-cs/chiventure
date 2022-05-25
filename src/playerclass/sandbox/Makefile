CC = gcc
BIN = custom_skills
SRCS = custom_skills.c custom_skills_main.c
RM = rm -f
INCLUDE = -I ../../../include
CFLAGS = -g -O2 $(INCLUDE)
LIBPATH = ../../../build/src/
UTLIST = common/
SFLAGS = -L$(LIBPATH)$(UTLIST) -lcommon

.PHONY = all
all: 
		$(CC) $(SRCS) $(CFLAGS) $(SFLAGS) -o $(BIN) 

.PHONY = clean
clean:
		$(RM) $(BIN)