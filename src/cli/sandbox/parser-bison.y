%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();

void yyerror(char* s);
%}

/* tokens */
%token CHR /* any character that isn't a space or a newline */
%token SPC /* a space */
%token EOL /* end of line, newline char */

%%
/* TODO */

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

