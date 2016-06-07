%code requires {
    #include <stdio.h>
    #include <stdint.h>
    #include "ast.h"
}
%code {
    #include <stdarg.h>
    #include "symtable.h"
    #include "lexer.h"
    #include "main-data.h"
    void yyerror(YYLTYPE* loc, struct MainData* p, const char*, ...);
    #define scan_info p->scaninfo
    int type;
}

%error-verbose
%locations
%verbose
%define api.pure
%defines "parser.h"
%lex-param {scan_info}
%parse-param {struct MainData* p}

%union {
    int32_t ivalue;
    float fvalue;
    char* svalue;
    ASTNode* node;
    int relop;
}

%token FUNCTION CONTINUE WHILE DO ARRAY PROCEDURE PROGRAM BYTE IF ELSE BREAK PRINTSTR WRITECHAR RELOP EXIT NULLL

%token <svalue> ID LOOP
%token <ivalue> INTEGER OR AND XOR NOT READCHAR READINT PRINTCHAR PRINTINT TYPE
%token <svalue> STRING
%token <fvalue> FLOAT

%type <ivalue> RELOP
%type <node> block inner_block item_list inst_list item declaration decl_list decl instruction assignment condition xor_expression and_expression not_expression comparison_exp expression term fact opnd ifthenelse inner_cont else_block loop
%type <node> array array_int

%expect 1   // else ambiguity

%%
program_file    :   PROGRAM ID '(' ')'
                    {
                        p->symtable->add($2, SymTable::PROGRAM);
                    }
                        block
                    {
                        if (p->no_of_errors > 0) return -1;
                            p->ast = new ASTProgram($2, $6);
                    }
                ;

block           :   '{' item_list '}'                   { $$ = $2; }
                ;

inner_block     :   '{' inst_list '}'                   { $$ = $2; }
                ;

item_list       :   /* epsilon */                       { $$ = NULL; }
                |   item_list item                      { $$ = new ASTSeq($1, $2); }
                ;


%%

void yyerror(YYLTYPE* loc, struct MainData* p, const char* s, ...)
{
    va_list ap;
    va_start(ap, s);

    if (loc->first_line)
    {
        fprintf(stderr, "%d.%d:%d.%d: ", loc->first_line, loc->first_column,
                loc->last_line, loc->last_column);
    }
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    p->no_of_errors++;
}

