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

{comment1}  {}

"/*"        { yycolumn+=yyleng; BEGIN(COMM); }
<COMM>.     { yycolumn+=yyleng; }
<COMM>"\n"  { yycolumn = 1; }
<COMM>"*/"  { yycolumn+=yyleng; BEGIN(INITIAL); }

[ \t]       {yycolumn+=yyleng; } 

.           { UPDATE_LOC; return yytext[0]; }

\n          { yycolumn = 0; }

%%

