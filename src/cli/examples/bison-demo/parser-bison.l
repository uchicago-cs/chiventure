%option noyywrap noinput nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser-bison.tab.h"

%}

%%

    /* this takes in start of line and "open" and returns the token OPEN */
^open { return OPEN; }

close { return CLOSE; }

push { return PUSH; }

pull { return PULL; }

turn_on { return TURN_ON; }

turn_off { return TURN_OFF; }

take { return TAKE; }

pickup { return PICKUP; }

drop { return DROP; }

consume { return CONSUME; }

the+ { return THE; }

^GO|go|Go|gO|head|move|walk  { return GO; }

TO|to|To|tO   { return TO; }

^fight|battle { return FIGHT; }

^put|PUT { return PUT; }

^use|USE { return USE; }

^view|VIEW { return VIEW; }

credits { return CREDITS; }

my { return MY; }

on { return ON; }

[a-zA-Z0-9]+  { 
    yylval.word = strdup(yytext);
    return WORD; }

\n               { return EOL; }

[ \t]      { /* ignore whitespace */ }

. { /* unknown character */ }

%%
