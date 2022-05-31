BIN = bison-demo
CC = gcc
BISON = bison
CFLAGS = -Wall -I../../../../include -I.
FLEX = flex
RM = rm -f

bison-demo: bison-demo_parse bison-demo_lex
	$(CC) $(LDFLAGS) $(CFLAGS) -o bison-demo bison-demo.c out/bison-demo.tab.c out/bison-demo.yy.c -lm

bison-demo_parse: bison-demo.y
	$(BISON) -d -o out/bison-demo.tab.c bison-demo.y

bison-demo_lex: bison-demo.l
	$(FLEX) -o out/bison-demo.yy.c bison-demo.l

clean:
	$(RM) out/* $(BIN)

.PHONY: words clean
