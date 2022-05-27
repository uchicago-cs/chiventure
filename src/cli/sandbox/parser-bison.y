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
%token<word> OPEN
%token<word> CLOSE
%token<word> PUSH
%token<word> PULL
%token<word> TURN_ON 
%token<word> TURN_OFF
%token<word> TAKE 
%token<word> PICKUP
%token<word> DROP
%token<word> CONSUME 
%token<word> DRINK 
%token<word> EAT
%token THE
%token PUT
%token<word> USE
%token VIEW
%token<word> CREDITS
%token<word> WORD

%type<word_list> kind1_cmd
%type<word_list> kind1_cmd_keyword

%type<word_list> kind2_action
%type<word_list> kind2_action_keyword

%type<word_list> kind3_action
%type<word_list> kind3_action_keyword

%type<word_list> kind4_action
%type<word_list> kind4_action_keyword

%type<word_list> phrase 
%type<word_list> go_cmd
%type<word_list> fight_cmd
%type<word_list> credits_cmd
/*%type<word_list> put_cmd
%type<word_list> use_cmd
%type<word_list> view_cmd
*/
%%
line
  : 
  | line go_cmd EOL { handle_go_cmd($2); }
  | line kind1_cmd phrase EOL { handle_kind1_cmd($2); }
  | line fight_cmd EOL { handle_fight_cmd($2); }
  | line credits_cmd EOL { handle_credits_cmd($2); }
  | line phrase EOL { handle_cmd($2); }
  ;

kind1_cmd
  : kind1_cmd_keyword { $$ = $1; }
  | kind1_cmd_keyword THE { $$ = $1; }
  ;

kind1_cmd_keyword
  : OPEN { $$ = start_phrase($1); }
  | CLOSE { $$ = start_phrase($1); }
  | PUSH { $$ = start_phrase($1); }
  | PULL { $$ = start_phrase($1); }
  | TURN_ON { $$ = start_phrase($1); }
  | TURN_OFF { $$ = start_phrase($1); }
  | TAKE { $$ = start_phrase($1); }
  | PICKUP { $$ = start_phrase($1); }
  | DROP { $$ = start_phrase($1); }
  | CONSUME { $$ = start_phrase($1); }
  | USE { $$ = start_phrase($1); }
  | DRINK { $$ = start_phrase($1); }
  | EAT { $$ = start_phrase($1); }
  ;

/*
kind2_action
  : kind2_action_keyword { $$ = $1; }
  | kind2_action_keyword THE { $$ = $1; }
  ;

kind2_action_keyword
  : OPEN  { $$ = start_phrase($1); }
  | CLOSE  { $$ = start_phrase($1); }
  ;

kind3_action
  : kind3_action_keyword { $$ = $1; }
  | kind3_action_keyword THE { $$ = $1; }
  ;

kind3_action_keyword
  : OPEN  { $$ = start_phrase($1); }
  | CLOSE  { $$ = start_phrase($1); }
  ;

kind4_action
  : kind4_action_keyword { $$ = $1; }
  | kind4_action_keyword THE { $$ = $1; }
  ;

kind4_action_keyword
  : OPEN  { $$ = start_phrase($1); }
  | CLOSE  { $$ = start_phrase($1); }
  ;
*/
/*
  | line fight_cmd EOL { handle_fight_cmd($2); }
  | line credits_cmd EOL { handle_credits_cmd($2); }
  | line phrase EOL { handle_cmd($2); }
  | line put_cmd EOL { handle_put_cmd($2); }
  | line use_cmd EOL { handle_use_cmd($2); }
  | line view_cmd EOL { handle_view_cmd($2); }
*/  
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

/*
put_cmd
  : PUT { $$ = NULL; }
  | PUT phrase { $$ = $2; }
  ;

use_cmd
  : USE { $$ = NULL; }
  | USE phrase { $$ = $2; }
  ;

view_cmd
  : VIEW { $$ = NULL; }
  | VIEW phrase { $$ = $2; }
  ;
*/

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


