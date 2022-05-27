%option noyywrap noinput nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser-bison.tab.h"

%}

%%

    /* this takes in start of line and "open" and returns the token OPEN */
^open { return OPEN; }

the { return THE; }

^GO|go|Go|gO|head|move|walk  { return GO; }

TO|to|To|tO   { return TO; }

^fight|battle { return FIGHT; }

^put|PUT { return PUT; }

^use|USE { return USE; }

^view|VIEW { return VIEW; }

credits { return CREDITS; }

[a-zA-Z0-9]+  { 
    yylval.word = strdup(yytext);
    return WORD; }

\n               { return EOL; }

[ \t]      { /* ignore whitespace */ }

. { /* unknown character */ }

%%
