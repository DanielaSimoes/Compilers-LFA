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

id                      [A-Za-z_][A-Za-z0-9_]*
hexadecimal             [+-]?0[Xx][0-9A-Fa-f]{1,8}
decimal                 [+-]?[0-9]+
float                   [+-]?(([0-9]*\.)*[0-9]+)|(\.[0-9]+)|([0-9]+\.)
char		            ('.'|'\\n'|'\\t'|'\\r')
string		            (\"[^"]*\")
whitespace              [ \r\t]*
type                    (int|float|string|byte|char)

comment1                "//".*
comment2                "/*"

%x COMM

%%

"null"                  { UPDATE_LOC; yylval->ivalue = 0; return NULL; }
"program"               { UPDATE_LOC; return PROGRAM; }
"function"              { UPDATE_LOC; return FUNCTION; }
"procedure"             { UPDATE_LOC; return PROCEDURE; }

"void"                  { UPDATE_LOC; yylval -> svalue = strdup(yytext); return TYPE; }

"if"                    { UPDATE_LOC; return IF; }
"else"                  { UPDATE_LOC; return ELSE; }
"loop"                  { UPDATE_LOC; return LOOP; }
"break"                 { UPDATE_LOC; return BREAK; }
"continue"              { UPDATE_LOC; return CONTINUE; }
"while"                 { UPDATE_LOC; return WHILE; }
"do"                    { UPDATE_LOC; return DO; }

"exit()"                { UPDATE_LOC; return EXIT; }
"writeChar"             { UPDATE_LOC; return WRITECHAR; }
"printInt"              { UPDATE_LOC; return PRINTINT; }
"printStr"              { UPDATE_LOC; return PRINTSTR; }
"printChar"             { UPDATE_LOC; return PRINTCHAR; }
"readInt()"             { UPDATE_LOC; return READINT; }
"readChar()"            { UPDATE_LOC; return READCHAR; }

"=="                    { UPDATE_LOC; yylval->ivalue = 0; return RELOP; }
"!="                    { UPDATE_LOC; yylval->ivalue = 1; return RELOP; }
"<"                     { UPDATE_LOC; yylval->ivalue = 2; return RELOP; }
"<="                    { UPDATE_LOC; yylval->ivalue = 3; return RELOP; }
">"                     { UPDATE_LOC; yylval->ivalue = 4; return RELOP; }
">="                    { UPDATE_LOC; yylval->ivalue = 5; return RELOP; }

"or"                    { UPDATE_LOC; return OR; }
"and"                   { UPDATE_LOC; return AND; }
"xor"                   { UPDATE_LOC; return XOR; }
"not"                   { UPDATE_LOC; return NOT; }

{type}\[{decimal}\]     { UPDATE_LOC; yylval -> svalue = strdup(yytext); return ARRAY; }

"byte"                  { UPDATE_LOC; yylval->ivalue = 0; return TYPE; }
"int"                   { UPDATE_LOC; yylval->ivalue = 1; return TYPE; }
"float"                 { UPDATE_LOC; yylval->ivalue = 2; return TYPE; }
"boolean"               { UPDATE_LOC; yylval->ivalue = 3; return TYPE; }
{id}                    { UPDATE_LOC; yylval->svalue = strdup(yytext); return ID; }
{hexadecimal}           { UPDATE_LOC; yylval->ivalue = (int32_t)strtol(yytext, NULL, 0); return INTEGER; }
{decimal}               { UPDATE_LOC; yylval->ivalue = atoi(yytext); return INTEGER; }
{float}                 { UPDATE_LOC; yylval->fvalue = atof(yytext); return FLOAT; }
{char}                  { UPDATE_LOC; yylval->svalue = strdup(yytext); return INTEGER; }
{string}                { UPDATE_LOC; yylval->svalue = strdup(yytext); return STRING; }

{comment1}              {}

"/*"                    { yycolumn+=yyleng; BEGIN(COMM); }
<COMM>.                 { yycolumn+=yyleng; }
<COMM>"\n"              { yycolumn = 1; }
<COMM>"*/"              { yycolumn+=yyleng; BEGIN(INITIAL); }

[ \t]                   {yycolumn+=yyleng; }

\n                      { yycolumn = 0; }

.                       { UPDATE_LOC; return yytext[0]; }


%%