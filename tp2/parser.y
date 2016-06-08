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

inst_list       :   /* epsilon */                       { $$ = NULL; }
                |   inst_list instruction               { $$ = new ASTSeq($1, $2); }
                ;

item            :   instruction                         { $$ = $1; }
                |   declaration                         { $$ = $1; }
                |   block                               { $$ = $1; }
                ;

declaration     :   TYPE { type = $1; } decl_list ';'   { $$ = $3; }
                ;

decl_list       :   decl                                { $$ = $1; }
                |   decl_list ',' decl                  { $$ = new ASTSeq($1, $3); }
                ;

decl            :   ID
                    {
                        $$ = new ASTSpaceDecl($1,4);
                        if (!p->symtable->add($1, type)) {
                            // duplicated var name
                        }
                    }
                |   ID '=' INTEGER
                    {
                        $$ = (type==ASTNode::INT) ? (ASTValue*) new ASTIntDecl($1, $3) : (ASTValue*) new ASTFloatDecl($1, $3);
                        if (!p->symtable->add($1, type)) {
                            // duplicated var name
                        }
                    }
                |   ID '=' FLOAT                        {
                        if (type==ASTNode::INT) {
                            // error
                        }
                        else {
                            $$ = new ASTFloatDecl($1, $3);
                            if (!p->symtable->add($1, type)) {
                                // duplicated var name
                            }
                        }
                    }
                |   ID '=' STRING
                    {
                        $$ = new ASTStringDecl($1, $3);
                        if (!p->symtable->add($1, type)) {
                            // duplicated var name
                        }
                    }
                |   ID '[' INTEGER ']'
                    {
                        $$ = new ASTSpaceDecl($1, 4 * $3);
                        if (!p->symtable->add($1, type)) {
                            // duplicated var name
                        }
                    }
                |   ID '[' ']' '=' '{' array '}'
                    {
                        $$ = new ASTArrayHead($1, ASTArrayHead::NOT_DEFINED, $6);
                        if (!p->symtable->add($1, type)) {
                            // duplicated var name
                        }
                        ASTIntegerArrayValue::elems = 0;
                    }
                |   ID '[' INTEGER ']' '=' '{' array '}'
                {
                    $$ = new ASTArrayHead($1, $3, $7);
                    if (!p->symtable->add($1, type)) {
                        // duplicated var name
                    }
                    if (ASTIntegerArrayValue::elems > ASTArrayHead::cur_size) {
                        // warning: truncate elements
                    }
                    else if (ASTIntegerArrayValue::elems < ASTArrayHead::cur_size) {
                        // warning: fill with zeroes
                    }
                    ASTIntegerArrayValue::elems = 0;
                }
                ;

array           :   array_int                           { $$ = $1; }
//                |   array_float                         { }
//                |   array_byte                          { }
//                |   array_char
                ;

array_int       :   array_int ',' INTEGER               { $$ = new ASTSeq($1, new ASTIntegerArrayValue($3)); }
                |   INTEGER                             { $$ = new ASTIntegerArrayValue($1); }
                ;

//array_float     :   array_float ',' FLOAT
//                |   FLOAT
//                ;

//array_byte      :   array_byte ',' BYTE
//                |   BYTE
//                ;

//array_char      :   array_char ',' CHAR
//                |   CHAR
//                ;


instruction     :   ifthenelse                          { $$ = $1; }
                |   loop                                { $$ = $1; }
                |   assignment ';'                      { $$ = $1; }
                |   BREAK ';'                           { $$ = new ASTBreak(); }
                |   PRINTINT '(' expression ')' ';'     { $$ = new ASTPrint($1, (ASTValue*) $3); }
                |   PRINTSTR '(' STRING ')' ';'
                    {
                        char s[2];
                        strcpy(s, std::to_string(ASTPrintStr::gcnt).c_str());
                        char c[4] = "s";
                        strcat(c,s);
                        if (!(p -> symtable -> getType(c, NULL)))
                            p -> symtable -> add(c, SymTable::BYTEARRAY);
                        $$ = new ASTPrintStr($3);
                    }

                |   ID '=' READINT ';'                  { $$ = new ASTAssignToVar($1, ASTNode::INT, new ASTFunctionCall($3)); }
                |   PRINTCHAR '(' INTEGER ')' ';'       { $$ = new ASTPrint($1, new ASTIntegerValue($3)); }
                |   EXIT ';'                            { $$ = new ASTExit(); }
                ;

assignment      :   ID '+''+'                           { $$ = new ASTOperation(ASTNode::ADD, new ASTVarValue($1, type), new ASTIntegerValue(1)); }
                |   ID '-''-'                           { $$ = new ASTOperation(ASTNode::SUB, new ASTVarValue($1, type), new ASTIntegerValue(1)); }
                |   ID  '=' expression
                    {
                        if (!(p -> symtable -> getType($1, &type)))
                        {
                            // label nao existe
                        } else if (type == ASTNode::FLOAT && ((ASTValue*)$3)->type == ASTNode::INT) {
                            $$ = new ASTAssignToVar($1, type, new ASTCast(ASTNode::FLOAT, (ASTValue*) $3));
                        } else if (type == ASTNode::INT && ((ASTValue*)$3)->type == ASTNode::FLOAT) {
                            $$ = new ASTAssignToVar($1, type, new ASTCast(ASTNode::INT, (ASTValue*) $3));
                        } else {
                            $$ = new ASTAssignToVar($1, type, (ASTValue*) $3);
                        }
                    }
                |   ID '=' STRING
                    {
                        if (!(p -> symtable -> getType($1, &type))) {
                            // label nao existe
                        } else {
                            $$ = new ASTAssignToVar($1, type, new ASTStringValue($3));
                        }
                    }
                ;

condition       :   xor_expression                      { $$ = $1; }
                |   condition OR xor_expression         { $$ = new ASTOperation($2, (ASTValue*) $1, (ASTValue*) $3); }
                ;

xor_expression  :   and_expression                      { $$ = $1; }
                |   xor_expression XOR and_expression   { $$ = new ASTOperation($2, (ASTValue*) $1, (ASTValue*) $3); }
                ;

and_expression  :   not_expression                      { $$ = $1; }
	            |   and_expression AND not_expression   { $$ = new ASTOperation($2, (ASTValue*) $1, (ASTValue*) $3); }
                ;

not_expression  :   comparison_exp                      { $$ = $1; }
                |   NOT comparison_exp                  { $$ = new ASTOperation($1, (ASTValue*) $2, NULL); }
                ;


comparison_exp  :   expression RELOP expression         { $$ = new ASTRelop($2, (ASTValue*) $1, (ASTValue*) $3); }
                |   '(' condition ')'                   { $$ = $2; }
                ;

expression      :	term                     { $$ = $1; }
                |	expression '+' term      { $$ = new ASTOperation(ASTNode::ADD, (ASTValue*) $1, (ASTValue*) $3); }
                |	expression '-' term      { $$ = new ASTOperation(ASTNode::SUB, (ASTValue*) $1, (ASTValue*) $3); }
                ;

term            :   fact                    { $$ = $1; }
                |   term '*' fact           { $$ = new ASTOperation(ASTNode::MUL, (ASTValue*) $1, (ASTValue*) $3); }
                |   term '/' fact           { $$ = new ASTOperation(ASTNode::DIV, (ASTValue*) $1, (ASTValue*) $3); }
                |   term '%' fact           { $$ = new ASTOperation(ASTNode::REM, (ASTValue*) $1, (ASTValue*) $3); }
                ;

fact            :   opnd                    { $$ = $1; }
                |   '(' TYPE ')' opnd       { $$ = new ASTCast($2, (ASTValue*) $4); } // v falta validar
                |   '-' fact                { $$ = new ASTOperation(ASTNode::NEG, (ASTValue*) $2, NULL); }
                ;

opnd            :   INTEGER                 { $$ = new ASTIntegerValue($1); }
                |   FLOAT                   { $$ = new ASTFloatValue($1); }
                |   ID                      { int type; p->symtable->getType($1, &type); $$ = new ASTVarValue($1, type); }
                |   READCHAR ';'            { $$ = new ASTFunctionCall($1); }
                |   READINT ';'             { $$ = new ASTFunctionCall($1); }
                |	'(' expression ')'      { $$ = $2; }
                ;

ifthenelse      :   IF '(' condition ')' inner_cont else_block  { $$ = new ASTIf((ASTValue*) $3, $5, $6); }
                ;

inner_cont      :   inner_block             { $$ = $1; }
                |   instruction             { $$ = $1; }
                ;

else_block      :   /* epsilon */           { $$ = NULL; }
                |   ELSE inner_cont         { $$ = $2; }
                ;

loop            :   LOOP inner_cont         { $$ = new ASTLoop($2); }
                ;

%%

void yyerror(YYLTYPE* loc, struct MainData* p, const char* s, ...) {
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
