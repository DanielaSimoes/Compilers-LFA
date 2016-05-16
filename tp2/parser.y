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
}

%error-verbose
%locations
%verbose
%define api.pure
%defines "parser.h"
%lex-param {scan_info}
%parse-param {struct MainData* p}

%union
{
    int32_t ivalue;
    float fvalue;
    char* svalue;
    ASTNode* node;
    ASTValue* nvalue;
    int relop;
    /* ... */
}

%token PROGRAM 

%token <svalue> ID 

%type <node>   outer_block di_seq 
%type <node>   decl inst

%%

program_file    :   PROGRAM ID '(' ')'
                        {
                            p->symtable->add($2, SymTable::PROGRAM);
                        }
                            outer_block
                        { 
                            if (p->no_of_errors > 0) return -1;
                            p->ast = new ASTProgram($2, $6);
                        }
                ;

outer_block     :   '{' di_seq '}'                  { $$ = $2; }
                ;

di_seq          :                                   { $$ = NULL; }
                |   di_seq decl                     { $$ = new ASTSeq ($1, $2); }
                |   di_seq inst                     { $$ = new ASTSeq ($1, $2); }
                |   di_seq error ';'                { $$ = $1; }
                |   di_seq error '}'                { $$ = $1; }
                ;

decl            :   'd' ';'        { $$ = NULL; }
                ;

inst            :   'i' ';'        { $$ = NULL; }
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

