%code top {
    #include <stdint.h>
}
%code {
    #include "lsm-lexer.h"
    void yyerror(YYLTYPE* loc, struct LSMData* p, const char*);
    #include "lsm-data.h"
    #define scanner p->scanner
}

%error-verbose
%locations
%verbose
%define api.pure
%defines "lsm-parser.h"
%lex-param {scanner}
%parse-param {struct LSMData* p}

%union
{
    uint8_t opcode;
    float vfloat;
    int32_t vint;
    char* vstr;
}

%token <vstr> HEXADECIMAL
%token <vint> DECIMAL
%token <vfloat> FLOAT
%token <vstr> CHAR
%token <vstr> STRING
%token <vstr> INTOP
%token <vstr> REALOP
%token <vstr> RET
%token <vstr> JUMPOP
%token <vstr> BIPUSH
%token <vstr> IPUSH
%token <vstr> FPUSH
%token <vstr> MEMACCESS
%token <vstr> STACK
%token <vstr> NOP
%token <vstr> HALT
%token <vstr> READ
%token <vstr> WRITE
%token <vstr> DIRBYTE
%token <vstr> DIRWORD
%token <vstr> DIRFLOAT
%token <vstr> DIRSTRING
%token <vstr> DIRSPACE
%token <vstr> LABELASM
%token <vstr> LABEL
%token <vstr> WHITESPACE
%token <vstr> DIRDATA
%token <vstr> DIRTEXT
%start lsm


%%

lsm         :   block_list
            |   '\n' lsm
			;

block_list	:	block
			|	block_list block
			;

block		:	text_block
			|	data_block
            |   error '\n' { yyerrok; }
			;

nline_block :   '\n'
            |   nline_block '\n'
            ;

data_block	:	DIRDATA nline_block
            |   DIRDATA nline_block data_body
            ;

data_body   :   data_line nline_block
            |   data_body data_line nline_block
            ;

data_line   :   LABEL ':' decl
            ;

decl        :   dir_byte
            |   dir_word
            |   dir_float
            |   dir_string
            |   dir_space
            ;

dir_byte    :   DIRBYTE byte_args
            ;

text_block	:	't' '\n'
			;

data_block	:	'd' '\n'


%%

#include <stdio.h>

void yyerror(YYLTYPE* loc, struct LSMData* p, const char* s)
{
    fprintf(stderr, "@ line %d: columns %d-%d: %s\n",
            loc->first_line, loc->first_column, loc->last_column, s);
}
