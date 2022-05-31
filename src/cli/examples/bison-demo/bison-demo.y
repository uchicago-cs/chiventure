%code requires {
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bison-demo.h"

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
%token<word> WORD

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

/* pattern types all return and pass along word_ll structs */
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

/* line specifies patterns for each line of input 
 * 
 * Each line ends with an EOL token (newline)
 * The 'line' at the beginning of each pattern represents the previously inputed line.
 * Note the first case, the empty line.
 *
 * The last pattern matches with input with no specified tokens in it (partial catch-all).
 */
line
  : 
  | line kind1_cmd EOL { handle_kind1_cmd($2, NULL); } //kind 1 action, no specified item
  | line kind1_cmd phrase EOL { handle_kind1_cmd($2, $3); } //kind 1 action with item
  | line kind2_cmd EOL { handle_kind2_cmd(NULL); } //kind 2 action, no specified path
  | line kind2_cmd phrase EOL { handle_kind2_cmd($3); } //kind2 action with path
  | line kind3_cmd EOL { handle_kind3_cmd($2, NULL, NULL); } //kind3 action with no specified items
  | line kind3_cmd kind3_item EOL { handle_kind1_cmd($2, $3); } //for special case "use", which is both kind 3 and 1 
  | line kind3_cmd kind3_item ON kind3_item EOL { handle_kind3_cmd($2, $3, $5); } //kind 3 action with two items
  | line kind4_cmd EOL { handle_kind4_cmd($2, NULL); } //kind 4 action with no specified self attribute
  | line kind4_cmd phrase EOL { handle_kind4_cmd($2, $3); } //kind 4 action with self attribute
  | line misc_cmd EOL { handle_misc_cmd($2, NULL); } //other action with no object
  | line misc_cmd phrase EOL { handle_misc_cmd($2, $3); } //other action with object
  | line phrase EOL { handle_cmd($2); } 
  ;


/* See misc_cmd_keyword, except for kind 1 action commands.
 * Passed to line. */
kind1_cmd
  : kind1_cmd_keyword { $$ = $1; }
  | kind1_cmd_keyword THE { $$ = $1; }
  ;

/* See misc_cmd_keyword, except for kind 1 action commands.
 * Passed to kind1_cmd. */ 
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
  | DRINK { $$ = start_phrase("drink"); }
  | EAT { $$ = start_phrase("eat"); }
  ;


/* See misc_cmd, except for kind 2 action commands.
 * Passed to line. */
kind2_cmd
  : kind2_cmd_keyword { $$ = $1; }
  | kind2_cmd_keyword TO { $$ = $1; }
  | kind2_cmd_keyword TO THE { $$ = $1; }
  ;

/* See misc_cmd_keyword, except for kind 2 action commands. 
 * Passed to kind2_cmd. */
kind2_cmd_keyword
  : GO { $$ = start_phrase("go"); }
  ;


/* This is just like misc_cmd, but the filtering of words that modify the items
 * is done in kind3_item. This exists for cases where words modifying the action
 * or other filler words need to be filtered.
 * Passed to line. */ 
kind3_cmd
  : kind3_cmd_keyword { $$ = $1; }
  ;

/* See misc_cmd_keyword, except for kind 3 action commands. 
 * Passed to kind3_cmd. */
kind3_cmd_keyword
  : USE { $$ = start_phrase("use"); }
  | PUT { $$ = start_phrase("put"); }
  ;

/* Similar to misc_cmd, in that it filters out the tokens that modify the items
 * in the input. This is done separately from kind3_cmd since there are two items
 * in kind 3 actions.
 * Passed to line. */
kind3_item
  : THE phrase { $$ = $2; }
  | phrase
  | MY phrase { $$ = $2; }
  ;


/* See misc_cmd_keyword, except for kind 4 action commands.
 * Passed to line. */
kind4_cmd
  : kind4_cmd_keyword { $$ = $1; }
  | kind4_cmd_keyword THE { $$ = $1; }
  | kind4_cmd_keyword MY { $$ = $1; }
  ;

/* See misc_cmd_keyword, except for kind 4 action commands. 
 * Passed to kind4_cmd. */
kind4_cmd_keyword
  : VIEW { $$ = start_phrase("view"); }
  ;


/* This pattern type matches to an action command keyword and subsequent articles,
 * prepositions, and/or pronouns that may occur before the object of the command.
 * 
 * The point of this pattern type is to filter out these extra words. Only the first
 * argument, the keyword, is passed to line.
 */
misc_cmd
  : misc_cmd_keyword { $$ = $1; }
  | misc_cmd_keyword THE { $$ = $1; }
  | misc_cmd_keyword TO { $$ = $1; }
  | misc_cmd_keyword TO THE { $$ = $1; }
  ;

/* This pattern type matches to each individual token defined as an action that doesn't fit
 * one of the four action kinds.
 * 
 * A linked list is instantiated with the word being the action command. It is passed to misc_cmd.
 */
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


/* The backbone of the parsing mechanism 
 * 
 * This recursively builds a linked list of words. The first word instantiates the linked list,
 * and following words are appended. 
 * 
 * Note that other defined tokens are different from WORD. In this demo, phrases usually match
 * with the object of the action. */
phrase
  : WORD { $$ = start_phrase($1); }
  | phrase WORD { $$ = append_to_phrase($1, $2); }
  ;

%%


/* yyparse is the mechanism for prompting for input, found in the Bison library */
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


