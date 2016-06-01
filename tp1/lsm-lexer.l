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

hexadecimal   [+-]?0[Xx][0-9A-Fa-f]{1,8}
decimal       [+-]?[0-9]+
float         [+-]?(([0-9]*\.)*[0-9]+)|(\.[0-9]+)|([0-9]+\.)
char		  ('.'|'\\n'|'\\t'|'\\r')
string		  \"(\\.|[^"\\])*\"
dirdata       (\.data)
dirtext       (\.text)
dirbyte  	  (\.byte)
dirword		  (\.word)
dirfloat	  (\.float)
dirstring	  (\.string)
dirspace	  (\.space)
label         [A-Za-z_][A-Za-z0-9_]*
comment       ;[^\n\r]*
whitespace    [ \r\t]*

%%

\n              { yycolumn = 1; UPDATE_LOC; return '\n'; }
{hexadecimal}   { UPDATE_LOC; yylval->vint = (int32_t)strtol(yytext, NULL, 0); return INTEGER; }
{decimal}       { UPDATE_LOC; yylval->vint = atoi(yytext); return INTEGER; }
{float}         { UPDATE_LOC; yylval->vfloat = atof(yytext); return FLOAT; }
{char}          { UPDATE_LOC; yylval->vint = int(yytext[1]); return INTEGER; }
{string}        { UPDATE_LOC; yylval->vstr = strdup(yytext); return STRING; }
"iadd"          { UPDATE_LOC; yylval->opcode = 0x10; return INTOP;  }
"isub"          { UPDATE_LOC; yylval->opcode = 0x11; return INTOP;  }
"imul"          { UPDATE_LOC; yylval->opcode = 0x12; return INTOP;  }
"idiv"          { UPDATE_LOC; yylval->opcode = 0x13; return INTOP;  }
"irem"          { UPDATE_LOC; yylval->opcode = 0x14; return INTOP;  }
"ineg"          { UPDATE_LOC; yylval->opcode = 0x15; return INTOP;  }
"iand"          { UPDATE_LOC; yylval->opcode = 0x16; return INTOP;  }
"ior"           { UPDATE_LOC; yylval->opcode = 0x17; return INTOP;  }
"ixor"          { UPDATE_LOC; yylval->opcode = 0x18; return INTOP;  }
"ishl"          { UPDATE_LOC; yylval->opcode = 0x19; return INTOP;  }
"ishr"          { UPDATE_LOC; yylval->opcode = 0x1a; return INTOP;  }
"iushr"         { UPDATE_LOC; yylval->opcode = 0x1b; return INTOP;  }
"fadd"          { UPDATE_LOC; yylval->opcode = 0x20; return REALOP; }
"fsub"          { UPDATE_LOC; yylval->opcode = 0x21; return REALOP; }
"fmul"          { UPDATE_LOC; yylval->opcode = 0x22; return REALOP; }
"fdiv"          { UPDATE_LOC; yylval->opcode = 0x23; return REALOP; }
"frem"          { UPDATE_LOC; yylval->opcode = 0x24; return REALOP; }
"fneg"          { UPDATE_LOC; yylval->opcode = 0x25; return REALOP; }
"i2f"           { UPDATE_LOC; yylval->opcode = 0x26; return REALOP; }
"f2i"           { UPDATE_LOC; yylval->opcode = 0x27; return REALOP; }
"ret"           { UPDATE_LOC; yylval->opcode = 0x40; return RET; }
"goto"          { UPDATE_LOC; yylval->opcode = 0x30; return JUMPOP; }
"jsr"           { UPDATE_LOC; yylval->opcode = 0x31; return JUMPOP; }
"ifeq"          { UPDATE_LOC; yylval->opcode = 0x32; return JUMPOP; }
"ifne"          { UPDATE_LOC; yylval->opcode = 0x33; return JUMPOP; }
"iflt"          { UPDATE_LOC; yylval->opcode = 0x34; return JUMPOP; }
"ifge"          { UPDATE_LOC; yylval->opcode = 0x35; return JUMPOP; }
"ifgt"          { UPDATE_LOC; yylval->opcode = 0x36; return JUMPOP; }
"ifle"          { UPDATE_LOC; yylval->opcode = 0x37; return JUMPOP; }
"bipush"        { UPDATE_LOC; yylval->opcode = 0x50; return BIPUSH;}
"ipush"         { UPDATE_LOC; yylval->opcode = 0x51; return IPUSH;}
"fpush"         { UPDATE_LOC; yylval->opcode = 0x52; return FPUSH;}
"pop"           { UPDATE_LOC; yylval->opcode = 0x53; return STACK; }
"dup"           { UPDATE_LOC; yylval->opcode = 0x54; return STACK; }
"dup_x1"        { UPDATE_LOC; yylval->opcode = 0x55; return STACK; }
"dup2"          { UPDATE_LOC; yylval->opcode = 0x56; return STACK; }
"swap"          { UPDATE_LOC; yylval->opcode = 0x57; return STACK; }
"la"			{ UPDATE_LOC; yylval->opcode = 0x59; return MEMACCESS; }
"load"          { UPDATE_LOC; yylval->opcode = 0x60; return MEMACCESS; }
"store"         { UPDATE_LOC; yylval->opcode = 0x61; return MEMACCESS; }
"baload"        { UPDATE_LOC; yylval->opcode = 0x62; return STACK; }
"bastore"       { UPDATE_LOC; yylval->opcode = 0x63; return STACK; }
"iaload"        { UPDATE_LOC; yylval->opcode = 0x64; return STACK; }
"iastore"       { UPDATE_LOC; yylval->opcode = 0x65; return STACK; }
"faload"        { UPDATE_LOC; yylval->opcode = 0x66; return STACK; }
"fastore"       { UPDATE_LOC; yylval->opcode = 0x67; return STACK; }
"nop"           { UPDATE_LOC; yylval->opcode = 0x00; return NOP; }
"halt"          { UPDATE_LOC; yylval->opcode = 0xF0; return HALT; }
"read"          { UPDATE_LOC; yylval->opcode = 0xF1; return READ; }
"write"         { UPDATE_LOC; yylval->opcode = 0xF2; return WRITE; }
{dirdata}		{ UPDATE_LOC; return DIRDATA; }
{dirtext}		{ UPDATE_LOC; return DIRTEXT; }
{dirbyte}       { UPDATE_LOC; yylval->vstr = strdup(yytext); return DIRBYTE; }
{dirword}       { UPDATE_LOC; yylval->vstr = strdup(yytext); return DIRWORD; }
{dirfloat}      { UPDATE_LOC; yylval->vstr = strdup(yytext); return DIRFLOAT; }
{dirstring}     { UPDATE_LOC; yylval->vstr = strdup(yytext); return DIRSTRING; }
{dirspace}      { UPDATE_LOC; yylval->vstr = strdup(yytext); return DIRSPACE; }
{label}         { UPDATE_LOC; yylval->vstr = strdup(yytext); return LABEL; }
{comment}       { }
{whitespace}    { UPDATE_LOC; }
.               { UPDATE_LOC; return yytext[0]; }
%%
