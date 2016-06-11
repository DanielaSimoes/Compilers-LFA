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

%token FUNCTION CONTINUE WHILE DO ARRAY PROCEDURE PROGRAM IF ELSE BREAK PRINTSTR WRITECHAR RELOP EXIT NULLL

%token <svalue> ID LOOP
%token <ivalue> BYTE INTEGER OR AND XOR NOT READCHAR READINT PRINTCHAR PRINTINT TYPE INCDEC ASSIGN
%token <svalue> STRING
%token <fvalue> FLOAT

%type <ivalue> RELOP
%type <node> block inner_block item_list inst_list item declaration decl_list decl instruction assignment condition xor_expression and_expression not_expression comparison_exp expression term fact opnd ifthenelse inner_cont else_block loop
%type <node> array

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
                            yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                        }
                    }
                |   ID '=' INTEGER
                    {
                        $$ = (type==ASTNode::INT) ? (ASTValue*) new ASTIntDecl($1, $3) : (ASTValue*) new ASTFloatDecl($1, $3);
                        if (!p->symtable->add($1, type)) {
                            // duplicated var name
                            yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                        }
                    }
                |   ID '=' FLOAT
                    {
                        if (type==ASTNode::INT) {
                            yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                        }
                        else {
                            $$ = new ASTFloatDecl($1, $3);
                            if (!p->symtable->add($1, type)) {
                                yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                            }
                        }
                    }
                |   ID '=' STRING
                    {
                        $$ = new ASTStringDecl($1, $3);
                        if (!p->symtable->add($1, type)) {
                            yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                        }
                    }
                |   ID '[' INTEGER ']'
                    {
                        $$ = new ASTSpaceDecl($1, 4 * $3);
                        if (!p->symtable->add($1, type)) {
                            yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                        }
                    }
                |   ID '[' ']' '=' '{' array '}'
                    {
                        $$ = new ASTArrayHead(type, $1, ASTArrayHead::NOT_DEFINED, $6);
                        if (!p->symtable->add($1, type)) {
                            yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                        }
                        ASTArrayHead::elems = 0;
                    }
                |   ID '[' INTEGER ']' '=' '{' array '}'
                {
                    $$ = new ASTArrayHead(type, $1, $3, $7);
                    if (!p->symtable->add($1, type)) {
                        yyerror(&yylloc, p, YY_("error: duplicated variable name."));
                    }
                    if (ASTArrayHead::elems > ASTArrayHead::cur_size) {
                        // warning: ignore elements in excess
                        yyerror(&yylloc, p, YY_("warning: elements given exceed the defined array size."));
                        p->no_of_errors--;
                    }
                    else if (ASTArrayHead::elems < ASTArrayHead::cur_size) {
                        // warning: fill with zeroes
                        yyerror(&yylloc, p, YY_("warning: not enough elements given for the defined array size."));
                        p->no_of_errors--;
                    }
                    ASTArrayHead::elems = 0;
                }
                ;

array           :   array ','  '\'' INTEGER '\''
                    {
                        if (type == ASTNode::FLOAT){
                            yyerror(&yylloc, p, YY_("error: incompatible types."));
                        }else if($4 < 0 || $4 > 255){
                            yyerror(&yylloc, p, YY_("warning: number must be bounded between 0 and 255."));
                        }
                        else
                            $$ = new ASTSeq($1, new ASTByteArrayValue((char)$4));
                    }
                |    '\'' INTEGER '\''
                    {
                        if (type == ASTNode::FLOAT)
                            yyerror(&yylloc, p, YY_("error: incompatible types."));
                        else if ($2 < 0 || $2 > 255)
                            yyerror(&yylloc, p, YY_("warning: number must be bounded between 0 and 255."));
                        else
                            $$ = new ASTByteArrayValue((char)$2);
                    }
                |   array ',' INTEGER                   { $$ = new ASTSeq($1, new ASTIntegerArrayValue($3)); }
                |   INTEGER                             { $$ = new ASTIntegerArrayValue($1); }
                |   array ',' FLOAT
                    {
                        if (type == ASTNode::INT)
                            yyerror(&yylloc, p, YY_("error: incompatible types."));
                        else
                            $$ = new ASTSeq($1, new ASTFloatArrayValue((float)$3));
                    }
                |   FLOAT
                    {
                        if (type == ASTNode::INT)
                            yyerror(&yylloc, p, YY_("error: incompatible types."));
                        else
                            $$ = new ASTFloatArrayValue((float)$1);
                    }
                ;

instruction     :   ifthenelse  { $$ = $1; }
                |   loop                                { $$ = $1; }
                |   assignment ';'                      { $$ = $1; }
                |   BREAK ';'                           { $$ = new ASTBreak(); }
                |   PRINTINT '(' expression ')' ';'     { $$ = new ASTPrint($1, (ASTValue*) $3); }
                |   PRINTSTR '(' STRING ')' ';' {
                        char s[2];
                        strcpy(s, std::to_string(ASTPrintStr::gcnt).c_str());
                        char c[4] = "s";
                        strcat(c,s);
                        if (!(p -> symtable -> getType(c, NULL)))
                            p -> symtable -> add(c, SymTable::BYTEARRAY);
                        $$ = new ASTPrintStr($3);
                    }
                |   PRINTSTR '(' ID ')' ';' {
                        int idType = ASTNode::NONE;
                        if (!(p -> symtable -> getType($3, &idType)))
                            yyerror(&yylloc, p, YY_("error: variable doesn't exist."));
                        $$ = new ASTPrintStr(new ASTVarValue($3, ASTNode::STRING));
                    }
                |   ID '=' READINT ';'                  { $$ = new ASTAssignToVar($1, ASTNode::INT, new ASTFunctionCall($3)); }
                |   PRINTCHAR '(' expression ')' ';'    { $$ = new ASTPrint($1, (ASTValue*)$3); }
                |   EXIT ';'                            { $$ = new ASTExit(); }
                ;

assignment      :   ID INCDEC                           { $$ = new ASTAssignToVar($1, type, new ASTOperation($2, new ASTVarValue($1, type), new ASTIntegerValue(1))); }
                |   INCDEC ID                           { $$ = new ASTAssignToVar($2, type, new ASTOperation($1, new ASTVarValue($2, type), new ASTIntegerValue(1))); }
                |   ID  '=' expression
                    {
                        if (!(p -> symtable -> getType($1, &type)))
                        {
                            yyerror(&yylloc, p, YY_("error: variable doesn't exist."));
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
                            yyerror(&yylloc, p, YY_("error: variable doesn't exist."));
                        } else {
                            $$ = new ASTAssignToVar($1, type, new ASTStringValue($1, $3));
                        }
                    }
                |   ID ASSIGN expression
                    {
                        if (!(p -> symtable -> getType($1, &type)))   {
                            yyerror(&yylloc, p, YY_("error: variable doesn't exist."));
                        } else {
                            $$ = new ASTAssignToVar($1, type, new ASTOperation($2, new ASTVarValue($1, type) , (ASTValue*)$3));
                        }
                    }
                |   ID '[' expression ']' '=' expression {
                        if (!(p -> symtable -> getType($1, &type)))   {
                            yyerror(&yylloc, p, YY_("error: variable doesn't exist."));
                        } else if (((ASTValue*)$3)->getType() != ASTNode::INT) {
                            yyerror(&yylloc, p, YY_("error: array index must be an integer."));
                        } else if ( type == ASTNode::INT && ((ASTValue*)$6)->getType() == ASTNode::FLOAT) {
                            yyerror(&yylloc, p, YY_("error: incompatible types."));
                        } else if ( type == ASTNode::FLOAT && ((ASTValue*)$6)->getType() == ASTNode::INT) {
                            $$ = new ASTAssignToArrayElement($1, (ASTValue*)$3, new ASTCast(ASTNode::FLOAT, (ASTValue*)$6));
                        } else {
                            $$ = new ASTAssignToArrayElement($1, (ASTValue*)$3, (ASTValue*)$6);
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
                |   FLOAT                   { $$ = new ASTFloatValue((float)$1); }
                |   ID
                    {
                        if (!p->symtable->getType($1, &type)) {
                            yyerror(&yylloc, p, YY_("error: variable doesn't exist."));
                        } else {
                            $$ = new ASTVarValue($1, type);
                        }
                    }
                |   ID '[' expression ']'
                    {
                        if (!(p -> symtable -> getType($1, &type)))   {
                            yyerror(&yylloc, p, YY_("error: variable doesn't exist."));
                        } else {
                            $$ = new ASTArrayElementValue(type, $1, (ASTValue*) $3);
                        }
                    }
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
