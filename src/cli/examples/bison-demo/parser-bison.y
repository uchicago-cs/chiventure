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

/* prepositions, pronouns, articles to filter out */
%token TO
%token THE
%token MY
%token ON

/* actions that aren't kinds1-4 */
%token<word> QUIT
%token<word> HELP
%token<word> HIST
%token<word> CREDITS
%token<word> LOOK
%token<word> INV
%token<word> MAP
%token<word> SWITCH
%token<word> LOAD
%token<word> NAME
%token<word> PALETTE
%token<word> ITEMS
%token<word> TALK
%token<word> FIGHT

/* kind 1 */
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

/* kind 2 */
%token<word> GO

/* kind 3 */
%token<word>PUT
%token<word> USE

/* kind 4 */
%token<word> VIEW

%token<word> WORD


%type<word_list> kind1_cmd
%type<word_list> kind1_cmd_keyword

%type<word_list> kind2_cmd
%type<word_list> kind2_cmd_keyword

%type<word_list> kind3_cmd
%type<word_list> kind3_cmd_keyword
%type<word_list> kind3_item

%type<word_list> kind4_cmd
%type<word_list> kind4_cmd_keyword

%type<word_list> misc_cmd
%type<word_list> misc_cmd_keyword

%type<word_list> phrase 

%%
line
  : 
  | line kind1_cmd EOL { handle_kind1_cmd($2, NULL); }
  | line kind1_cmd phrase EOL { handle_kind1_cmd($2, $3); }
  | line kind2_cmd EOL { handle_kind2_cmd(NULL); }
  | line kind2_cmd phrase EOL { handle_kind2_cmd($3); }
  | line kind3_cmd EOL { handle_kind3_cmd($2, NULL, NULL); }
  | line kind3_cmd kind3_item EOL { handle_kind1_cmd($2, $3); } //for special case "use"
  | line kind3_cmd kind3_item ON kind3_item EOL { handle_kind3_cmd($2, $3, $5); }
  | line kind4_cmd EOL { handle_kind4_cmd($2, NULL); }
  | line kind4_cmd phrase EOL { handle_kind4_cmd($2, $3); }
  | line misc_cmd EOL { handle_misc_cmd($2, NULL); }
  | line misc_cmd phrase EOL { handle_misc_cmd($2, $3); }
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
//  | USE { $$ = start_phrase("use"); }
  | DRINK { $$ = start_phrase("drink"); }
  | EAT { $$ = start_phrase("eat"); }
  ;

kind2_cmd
  : kind2_cmd_keyword { $$ = $1; }
  | kind2_cmd_keyword TO { $$ = $1; }
  | kind2_cmd_keyword TO THE { $$ = $1; }
  ;

kind2_cmd_keyword
  : GO { $$ = start_phrase("go"); }
  ;

kind3_cmd
  : kind3_cmd_keyword { $$ = $1; }
  ;

kind3_cmd_keyword
  : USE { $$ = start_phrase("use"); }
  | PUT { $$ = start_phrase("put"); }
  ;

kind3_item
  : THE phrase { $$ = $2; }
  | phrase
  | MY phrase { $$ = $2; }
  ;

kind4_cmd
  : kind4_cmd_keyword { $$ = $1; }
  | kind4_cmd_keyword THE { $$ = $1; }
  | kind4_cmd_keyword MY { $$ = $1; }
  ;

kind4_cmd_keyword
  : VIEW { $$ = start_phrase("view"); }
  ;

misc_cmd
  : misc_cmd_keyword { $$ = $1; }
  | misc_cmd_keyword THE { $$ = $1; }
  | misc_cmd_keyword TO { $$ = $1; }
  | misc_cmd_keyword TO THE { $$ = $1; }
  ;

misc_cmd_keyword
  : QUIT { $$ = start_phrase("quit"); }
  | HELP { $$ = start_phrase("help"); }
  | HIST { $$ = start_phrase("hist"); }
  | CREDITS { $$ = start_phrase("credits"); }
  | LOOK { $$ = start_phrase("look"); }
  | INV  { $$ = start_phrase("inv"); }
  | MAP { $$ = start_phrase("map"); }
  | SWITCH { $$ = start_phrase("switch"); }
  | LOAD { $$ = start_phrase("load"); }
  | NAME  { $$ = start_phrase("name"); }
  | PALETTE { $$ = start_phrase("palette"); }
  | ITEMS { $$ = start_phrase("items"); } 
  | TALK { $$ = start_phrase("talk"); }
  | FIGHT { $$ = start_phrase("fight"); }
  ;

phrase
  : WORD { $$ = start_phrase($1); }
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


