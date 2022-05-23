BIN = parser-bison
CC = gcc
BISON = bison
CFLAGS = -Wall -I../../../include -I.
FLEX = flex
RM = rm -f

parser-bison: parser-bison_parse parser-bison_lex
	$(CC) $(LDFLAGS) $(CFLAGS) -o parser-bison ../src/parser.c ../src/util.c parser-bison.c out/parser-bison.tab.c out/parser-bison.yy.c -lm

parser-bison_parse: parser-bison.y
	$(BISON) -d -o out/parser-bison.tab.c parser-bison.y

parser-bison_lex: parser-bison.l
	$(FLEX) -o out/parser-bison.yy.c parser-bison.l

clean:
	$(RM) out/* $(BIN)

.PHONY: words clean
