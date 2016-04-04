%{
    #include <stdlib.h>

    #include <stdint.h>
    #include "lsm-parser.h"

    #define UPDATE_LOC yylloc->first_line = yylloc->last_line = yylineno; \
        yylloc->first_column = yycolumn; yylloc->last_column = yycolumn+yyleng-1; \
        yycolumn += yyleng;
%}

%option noyywrap
%option nounput noinput
%option nodefault yylineno
%option reentrant bison-bridge bison-locations
%option header-file="lsm-lexer.h"


%%

.           { UPDATE_LOC; return yytext[0]; }

\n          { yycolumn = 1; UPDATE_LOC; return '\n'; }

%%


