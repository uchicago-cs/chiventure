%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "parser-bison.tab.h"
%}

%%
[A-Za-z0-9*&#-]  { return CHR; }
" "              { return SPC; }
\n               { return EOL; }
[ \t]            { /* ignore whitespace */ }
.                { printf("Unknown character: %c\n", *yytext); }
%%

/* scans a null terminated string */
void set_input_string(const char* in) {
  yy_scan_string(in);
}

/* deletes the buffer state */
void end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}
