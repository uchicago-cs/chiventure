%code requires {
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser-bison.h"

extern int yylex();
extern int yyparse();

void yyerror(char* s);

}

// declare the types to be used by bison
%union {
  char *word;
  word_ll *word_list;
}

/* tokens */
%token EOL /* end of line, newline char */
%token GO
%token TO
%token<word> WORD

%type<word_list> phrase 
%type<word_list> go_cmd

%%
line
  : 
  | line go_cmd EOL { handle_go_cmd($2); }
  ;

go_cmd
  : GO TO phrase { $$ = $3; }
  | GO phrase { $$ = $2; }
  ;
  
phrase
  : WORD  { $$ = start_phrase($1); }
  | phrase WORD { $$ = append_to_phrase($1, $2); }
  ;
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

