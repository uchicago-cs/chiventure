%option noyywrap noinput nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser-bison.tab.h"

%}

%%

    /* this takes in start of line and "open" and returns the token OPEN */
^open|OPEN { return OPEN; }

close|CLOSE|shut|SHUT { return CLOSE; }

push|PUSH { return PUSH; }

pull|PULL { return PULL; }

turn_on { return TURN_ON; }

turn_off { return TURN_OFF; }

take|TAKE|grab|GRAB { return TAKE; }

pickup|PICKUP { return PICKUP; }

drop|DROP { return DROP; }

consume|CONSUME { return CONSUME; }

the+ { return THE; }

^GO|go|Go|gO|head|move|walk|travel  { return GO; }

TO|to|To|tO   { return TO; }

^quit|QUIT { return QUIT; }

^help|HELP { return HELP; }

^hist|HIST { return HIST; }

^credits|CREDITS { return CREDITS; }

^look|LOOK|where|WHERE { return LOOK; }

^inv|INV { return INV; }

^map|MAP { return MAP; }

^switch|SWITCH { return SWITCH; }

^load|LOAD { return LOAD; }

^name|NAME { return NAME; }

^palette|PALETTE { return PALETTE; }

^items|ITEMS { return ITEMS; }

^talk|TALK|speak|SPEAK { return TALK; }

^fight|FIGHT|battle|BATTLE { return FIGHT; }

^put|PUT|place|PLACE { return PUT; }

^use|USE { return USE; }

^view|VIEW { return VIEW; }

my { return MY; }

on { return ON; }

[a-zA-Z0-9]+  { 
    yylval.word = strdup(yytext);
    return WORD; }

\n               { return EOL; }

[ \t]      { /* ignore whitespace */ }

. { /* unknown character */ }

%%
