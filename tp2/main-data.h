#ifndef __MAIN_DATA__
#define __MAIN_DATA__

#include "lexer.h"
#include "symtable.h"
#include "ast.h"

typedef struct MainData
{
    yyscan_t scaninfo;          // lexer info
    SymTable* symtable;         // pointer to labels' symbol table
    ASTNode* ast;               // Abstract syntax tree
    int no_of_errors;           // number of errors during compilation
} MainData;

#endif

