%code top {
    #include <stdint.h>
}
%code {
    #include "lsm-lexer.h"
    #include "lsm-data.h"
    void yyerror(YYLTYPE* loc, struct LSMData* p, const char*);
    void increment_bss(struct LSMData* p, uint16_t increment);
    void increment_text_size(struct LSMData* p, int);
    void parse_byte(struct LSMData* p, uint8_t, uint8_t);
    void parse_word(struct LSMData* p, uint8_t, uint32_t);
    void parse_mem(struct LSMData* p, uint8_t, std::tuple<std::string, int16_t> tuple);
    void parse_jump(struct LSMData* p, uint8_t, std::tuple<std::string, int16_t> tuple);
    void parse_reg(struct LSMData* p, uint8_t);
    void push_word(struct LSMData* p, uint32_t);
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

%token <vint> INTEGER
%token <vfloat> FLOAT
%token <vstr> STRING
%token <opcode> INTOP
%token <opcode> REALOP
%token <opcode> RET
%token <opcode> JUMPOP
%token <opcode> BIPUSH
%token <opcode> IPUSH
%token <opcode> FPUSH
%token <opcode> MEMACCESS
%token <opcode> STACK
%token <opcode> NOP
%token <opcode> HALT
%token <opcode> READ
%token <opcode> WRITE
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

%type <vint> regular_inst

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

byte_args   :   FLOAT
            |   CHAR
            |   DECIMAL
            |   HEXADECIMAL                 // must be a HEXABYTE!
            |   FLOAT ',' byte_args
            |   CHAR ',' byte_args
            |   DECIMAL ',' byte_args
            |   HEXADECIMAL ',' byte_args   // must be a HEXABYTE!
            ;

dir_word    :   DIRWORD word_args
            ;

word_args   :   FLOAT
            |   DECIMAL
            |   HEXADECIMAL
            |   FLOAT ',' word_args
            |   DECIMAL ',' word_args
            |   HEXADECIMAL ',' word_args
            ;

dir_float   :   DIRFLOAT float_args
            ;

float_args  :   FLOAT
            |   DECIMAL
            |   FLOAT ',' float_args
            |   DECIMAL ',' float_args
            ;

dir_string  :   DIRSTRING STRING
            ;

dir_space   :   DIRSPACE DECIMAL
            |   DIRSPACE HEXADECIMAL
            ;

text_block	:   DIRTEXT nline_block
            |   DIRTEXT nline_block text_body
            ;

text_body   :   text_line nline_block
            |   text_body text_line nline_block
            ;

text_line   :   LABEL ':'
            |   LABEL ':'  instruction
            |   instruction
			;

instruction :   INTOP
            |   REALOP
            |   RET
            |   JUMPOP LABEL
            |   BIPUSH DECIMAL
            |   IPUSH DECIMAL
            |   IPUSH HEXADECIMAL
            |   FPUSH FLOAT
            |   MEMACCESS LABEL
            |   STACK
            |   NOP
            |   HALT
            |   READ
            |   WRITE
            ;

%%

#include <stdio.h>

void yyerror(YYLTYPE* loc, struct LSMData* p, const char* s)
{
    fprintf(stderr, "@ line %d: columns %d-%d: %s\n",
            loc->first_line, loc->first_column, loc->last_column, s);
}
