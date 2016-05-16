%{
    #include <stdlib.h>
    #include <stdint.h>

    #include "parser.h"
    #include "ast.h"

    #define UPDATE_LOC { \
        yylloc->first_line = yylloc->last_line = yylineno; \
        yylloc->first_column = yycolumn+1; \
        yycolumn += yyleng; \
        yylloc->last_column = yycolumn+yyleng; }
%}


%option noyywrap
%option nounput noinput
%option nodefault yylineno
%option reentrant bison-bridge bison-locations
%option header-file="lexer.h"

id          [a-z]

comment1    "//".*
comment2    "/*"

%x COMM

%%

"program"   { UPDATE_LOC; return PROGRAM; }
{id}        { UPDATE_LOC; yylval->svalue = strdup(yytext); return ID; }

{comment1}  {}

"/*"        { yycolumn+=yyleng; BEGIN(COMM); }
<COMM>.     { yycolumn+=yyleng; }
<COMM>"\n"  { yycolumn = 1; }
<COMM>"*/"  { yycolumn+=yyleng; BEGIN(INITIAL); }

[ \t]       {yycolumn+=yyleng; } 

.           { UPDATE_LOC; return yytext[0]; }

\n          { yycolumn = 0; }

%%

