%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();

void yyerror(char* s);
%}

/* tokens */
%token CMD /* command, a single word. not sure if this should be split b/w letters and numbers? can bison recognizes stretches of chars as one token? */
%token SPC /* a space */
%token EOL /* end of line, newline char? */

%%
/* TODO */
/* Can Bison recognize separate words as individual tokens? Do we need 
 * to come up with a mechanism for it to recognize a space as end of word?
 * The command line should stop looking for input when user types in 
 * newline. Bison should stop looking for words to add to the linked 
 * list of strings(tokenized commands struct) when it reads a new line. 
 * We need to create a mechanism for splitting the string from the command
 * line into smaller strings and putting each string into the tokenized
 * commands list 
 */
%%

int main(int argc, char **argv)
{
    yyparse();

    return 0;
}

void yyerror(char *s)
{
    fprintf(stderr, "parse error: %s\n", s);
    exit(1);
}

