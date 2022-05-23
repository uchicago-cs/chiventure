%option noyywrap noinput nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser-bison.tab.h"

%}

%%

^GO|go|Go|gO  { return GO; }

TO|to|To|tO   { return TO; }

^fight|battle { return FIGHT; }

credits { return CREDITS; }

[a-zA-Z]+  { 
    yylval.word = strdup(yytext);
    return WORD; }

\n               { return EOL; }

[ \t]      { /* ignore whitespace */ }


%%
