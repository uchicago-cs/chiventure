%option noyywrap noinput nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include "bison-demo.tab.h"

%}

    /* Lex operators reference: https://docs.oracle.com/cd/E19504-01/802-5880/6i9k05dgk/index.html#lex-36741 */

%%

    /* prepositions, articles, posessive pronouns to filter out */

the { return THE; }

TO|to|To|tO   { return TO; }

my { return MY; }

on { return ON; }


    /* ====================================================================== */
    /* kind 1 actions: ACTION <item> */

^open|OPEN { return OPEN; }

^close|CLOSE|shut|SHUT { return CLOSE; }

^push|PUSH { return PUSH; }

^pull|PULL { return PULL; }

^turn_on { return TURN_ON; }

^turn_off { return TURN_OFF; }

^take|TAKE|grab|GRAB { return TAKE; }

^pickup|PICKUP { return PICKUP; }

^drop|DROP { return DROP; }

^consume|CONSUME|drink|DRINK|eat|EAT { return CONSUME; }


    /* ====================================================================== */
    /* kind 2 actions: ACTION <path> */

^GO|go|Go|gO|head|move|walk|travel  { return GO; }


    /* ====================================================================== */
    /* kind 3 actions: ACTION <item> <item> */

^put|PUT|place|PLACE { return PUT; }

^use|USE { return USE; }    /* note: also a kind 1 action */


    /* ====================================================================== */
    /* kind 4 actions: ACTION <self> */

^view|VIEW { return VIEW; }


    /* ====================================================================== */
    /* actions that aren't kinds1-4 (misc) */

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


    /* ====================================================================== */

[a-zA-Z0-9]+  { //this recognizes any miscellaneous combination of letters and/or digits
    yylval.word = strdup(yytext);
    return WORD; }

\n  { return EOL; }     /* this recognizes newline character */

[ \t]      { /* ignore whitespace */ }

. { /* unknown character */ }

%%
