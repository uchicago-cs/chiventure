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

%type<word_list> kind2_cmd
%type<word_list> kind2_cmd_keyword

%type<word_list> kind4_cmd
%type<word_list> kind4_cmd_keyword

%type<word_list> phrase 
/*%type<word_list> go_cmd
%type<word_list> fight_cmd
%type<word_list> credits_cmd
*//*%type<word_list> put_cmd
%type<word_list> use_cmd
%type<word_list> view_cmd
*/
%%
line
  : 
  | line kind1_cmd EOL { handle_kind1_cmd($2, NULL); }
  | line kind1_cmd phrase EOL { handle_kind1_cmd($2, $3); }
  | line kind2_cmd EOL { handle_kind2_cmd(NULL); }
  | line kind2_cmd phrase EOL { handle_kind2_cmd($3); }
  | line kind4_cmd EOL { printf("kind4\n"); }
  | line kind4_cmd phrase EOL { printf("kind4\n"); }
//  | line fight_cmd EOL { handle_fight_cmd($2); }
//  | line credits_cmd EOL { handle_credits_cmd($2); }
  | line phrase EOL { handle_cmd($2); }
  ;

kind1_cmd
  : kind1_cmd_keyword { $$ = $1; }
  | kind1_cmd_keyword THE { $$ = $1; }
  ;

kind1_cmd_keyword
  : OPEN { $$ = start_phrase("open"); }
  | CLOSE { $$ = start_phrase("close"); }
  | PUSH { $$ = start_phrase("push"); }
  | PULL { $$ = start_phrase("pull"); }
  | TURN_ON { $$ = start_phrase("turn_on"); }
  | TURN_OFF { $$ = start_phrase("turn_off"); }
  | TAKE { $$ = start_phrase("take"); }
  | PICKUP { $$ = start_phrase("pickup"); }
  | DROP { $$ = start_phrase("drop"); }
  | CONSUME { $$ = start_phrase("consume"); }
  | USE { $$ = start_phrase("use"); }
  | DRINK { $$ = start_phrase("drink"); }
  | EAT { $$ = start_phrase("eat"); }
  ;


kind2_cmd
  : kind2_cmd_keyword { $$ = $1; }
  | kind2_cmd_keyword TO { $$ = $1; }
  | kind2_cmd_keyword TO THE { $$ = $1; }
  ;

kind2_cmd_keyword
  : GO  { $$ = start_phrase("go"); }
  ;
/*
kind3_action
  : kind3_action_keyword { $$ = $1; }
  | kind3_action_keyword THE { $$ = $1; }
  ;

kind3_action_keyword
  : OPEN  { $$ = start_phrase($1); }
  | CLOSE  { $$ = start_phrase($1); }
  ;
*/

kind4_cmd
  : kind4_cmd_keyword { $$ = $1; }
  | kind4_cmd_keyword THE { $$ = $1; }
  ;

kind4_cmd_keyword
  : VIEW  { $$ = start_phrase("view"); }
  ;

/*
  | line fight_cmd EOL { handle_fight_cmd($2); }
  | line credits_cmd EOL { handle_credits_cmd($2); }
  | line phrase EOL { handle_cmd($2); }
  | line put_cmd EOL { handle_put_cmd($2); }
  | line use_cmd EOL { handle_use_cmd($2); }
  | line view_cmd EOL { handle_view_cmd($2); }
*/  
  ;

/*
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
*/
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


