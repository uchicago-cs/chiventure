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

/* tokens defined in the .l file! */
%token EOL /* end of line, newline char */
%token GO
%token TO
%token FIGHT
%token OPEN
%token CLOSE
%token THE
%token<word> CREDITS
%token<word> WORD

%type<word> kind1_action
%type<word> kind1_action_keyword

%type<word_list> phrase 
%type<word_list> go_cmd
%type<word_list> fight_cmd
%type<word_list> credits_cmd

%%
line
  : 
  | line go_cmd EOL { handle_go_cmd($2); }
  | line kind1_action phrase EOL { printf("handling : [%s]\n",$2); }
  | line fight_cmd EOL { handle_fight_cmd($2); }
  | line credits_cmd EOL { handle_credits_cmd($2); }
  | line phrase EOL { handle_cmd($2); }
  ;

kind1_action
  : kind1_action_keyword { $$ = $1; }
  | kind1_action_keyword THE { $$ = $1; }
  ;

kind1_action_keyword
  : OPEN  { $$ = $1; }
  | CLOSE  { $$ = $1; }
  ;


go_cmd
  : GO TO phrase { $$ = $3; }
  | GO phrase { $$ = $2; }
  ;

fight_cmd
  : FIGHT { $$ = NULL; }
  | FIGHT phrase { $$ = $2; }
  ;

credits_cmd
  : CREDITS { $$ = start_phrase($1); }
  | phrase CREDITS { $$ = start_phrase($2); }
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

