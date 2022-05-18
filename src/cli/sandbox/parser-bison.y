%union {
    char c;
}

%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();

void yyerror(char* s);
%}

/* tokens */
%token <c> CHR /* any character that isn't a space or a newline */
%token <c> SPC /* a space */
%token <c> EOL /* end of line, newline char */
%token GO

%%
/* TODO */

: GO { printf("%s", $1); }
      ;
%%

/* Declarations */
void set_input_string(const char* in);
void end_lexical_scan(void);

/* This function parses a string */
int parse_string(const char* in) {
  set_input_string(in);
  int rv = yyparse();
  end_lexical_scan();
  return rv;
}

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

