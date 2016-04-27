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
    void parse_mem(struct LSMData* p, uint8_t, std::tuple<std::string, int16_t> tuple, YYLTYPE* loc);
    void parse_jump(struct LSMData* p, uint8_t, std::tuple<std::string, int16_t> tuple, YYLTYPE* loc);
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
            |   error '\n' { yyerrok; p -> error_cnt++; }
		    ;

nline_block :   '\n'
            |   nline_block '\n'
            ;

data_block	:   DIRDATA nline_block
            |   DIRDATA nline_block data_body
            ;

data_body   :   data_line nline_block
            |   data_body data_line nline_block
            ;

data_line   :   LABEL ':' dir_decl {
                    if(p -> first_time) {
                        std::tuple<std::string,int16_t> varTuple ("DATA",p -> data_size); p->lbl_table->add($1, varTuple); printf("%s%lu%d", " DATA_SIZE: ", p -> data.size(), p->data_size); p->data_size = p->data.size()/4; free($1);
                    }
                }
            |   LABEL ':' dir_space {
                    if(p -> first_time) {
                        std::tuple<std::string,int16_t> varTuple ("BSS",p -> bss_size); p->lbl_table->add($1, varTuple); free($1);
                    }
                }
            ;

dir_decl    :   dir_byte
            |   dir_word
            |   dir_float
            |   dir_string
            ;


dir_byte    :   DIRBYTE byte_args
            ;

byte_args   :   INTEGER  {
                    if (p -> first_time) {
                        if ($1 < -128 || $1 > 127) {
                            yyerror(&yylloc, p, YY_("warning: number must be bound between -128 and 127."));
                            p -> data.push_back($1 & 0xFF);
                        } else {
                            p -> data.push_back($1);
                            while (((p -> data.size()) % 4) != 0) {
                                p -> data.push_back(0);
                            }
                        }
                    }
                }
            |   INTEGER {
                    if (p -> first_time) {
                        if ($1 < -128 || $1 > 127) {
                            yyerror(&yylloc, p, YY_("warning: number must be bound between -128 and 127."));
                            p -> data.push_back($1 & 0xFF);
                        } else {
                            p -> data.push_back($1);
                        }
                    }
                } ',' byte_args
            ;

dir_word    :   DIRWORD word_args
            ;

word_args   :   INTEGER {
                    if (p -> first_time) {
                        push_word(p, $1);
                    }
                }
            |   word_args ',' INTEGER {
                    if (p -> first_time) {
                        push_word(p, $3);
                    }
                }
            ;

dir_float   :   DIRFLOAT float_args
            ;

float_args  :   FLOAT {
                    if (p -> first_time) {
                        unsigned char *fl; fl = (unsigned char*)&($1);
                        for (int i = 3; i != -1; i--) {
                        p -> data.push_back(fl[i]);
                        }
                    }
                }
            |   INTEGER {
                    if (p -> first_time) {
                        push_word(p, $1);
                    }
                }
            |   float_args ',' FLOAT    {
                    if (p -> first_time) {
                        unsigned char *fl; fl = (unsigned char*)&($3);
                        for (int i = 3; i != -1; i--)
                        p -> data.push_back(fl[i]);
                    }
                }
            |   float_args ','  INTEGER  {
                    if (p -> first_time) {
                        push_word(p, $3);
                    }
                }
            ;


dir_string  :   DIRSTRING STRING {
                    if (p -> first_time) {
                        for (int i = (strlen($2)*8)-1; i != -1; i-=8) {
                            p -> data.push_back(($2)[i] & 0x00FF);
                        }
                        p -> data.push_back(0);
                        while (((p -> data.size()) % 4) != 0) {
                            p -> data.push_back(0);
                        }
                     }
                }

dir_space   :   DIRSPACE INTEGER {
                    if (p -> first_time) {
                        increment_bss(p,($2+3)/4);
                    }
                }
            ;

text_block	:   DIRTEXT nline_block
            |   DIRTEXT nline_block text_body
            ;

text_body   :   text_line nline_block
            |   text_body text_line nline_block
            ;

text_line   :   text_label  instruction
            |   instruction
            |   text_label
		    ;

text_label  :   LABEL {
                    if(p -> first_time)  {
                        std::tuple<std::string,int16_t> varTuple ("TEXT",p -> text_size); // TEXT means label to a address in the text segment
                        p->lbl_table->add($1, varTuple);
                    }
                } ':'
            ;


instruction :   regular_inst      { if(p -> first_time) {increment_text_size(p, 1);} else { parse_reg(p,$1); }                                                     }
            |   JUMPOP LABEL      { if(p -> first_time) {increment_text_size(p, 3);} else { parse_jump(p, $1, p->lbl_table->getValue("TEXT", $2), &yylloc); free($2); } }
            |   BIPUSH INTEGER    { if(p -> first_time) {increment_text_size(p, 2);} else { parse_byte(p, $1, $2); } }
            |   IPUSH INTEGER     { if(p -> first_time) {increment_text_size(p, 5);} else { parse_word(p, $1, $2); } }
   	        |   FPUSH INTEGER     { if(p -> first_time) {increment_text_size(p, 5);} else { parse_word(p, $1, $2); } }
            |   FPUSH FLOAT       { if(p -> first_time) {increment_text_size(p, 5);} else { parse_word(p, $1, $2); } }
            |   MEMACCESS LABEL   { if(p -> first_time) {increment_text_size(p, 3);} else { parse_mem(p, $1, p->lbl_table->getValue("DATA", $2), &yylloc); free($2); } }
            ;

regular_inst:   INTOP { $$ = $1; }
            |   REALOP { $$ = $1; }
            |   RET { $$ = $1; }
            |   STACK { $$ = $1; }
            |   NOP { $$ = $1; }
            |   HALT { $$ = $1; }
            |   READ { $$ = $1; }
            |   WRITE { $$ = $1; }
            ;

%%

#include <stdio.h>

void yyerror(YYLTYPE* loc, struct LSMData* p, const char* s)
{
    fprintf(stderr, "@ line %d: columns %d-%d: %s\n",
            loc->first_line, loc->first_column, loc->last_column, s);
}

void increment_bss(struct LSMData* p, uint16_t increment) {
    // method to increment size of non-initialized variables (bss_size on lsm-data.h)
    p -> bss_size += increment;
}

void increment_text_size(struct LSMData* p, int t) {
    // method to increment size of text segment (text_size on lsm-data.h)
    p -> text_size += t;
}

void parse_reg(struct LSMData* p, uint8_t opcode) {
    // method to parse the regular instructions - identify operations (push back to text vector on lsm-data.h)
    p -> text.push_back(opcode);
}

void parse_byte(struct LSMData* p, uint8_t opcode, uint8_t byte){
    p -> text.push_back(opcode);
    p -> text.push_back(byte);
}

void parse_word(struct LSMData* p, uint8_t opcode, uint32_t word){
    p -> text.push_back(opcode);
    p -> text.push_back(word >> 24);
    p -> text.push_back((word >> 16) & 0x00FF);
    p -> text.push_back((word >> 8) & 0x00FF);
    p -> text.push_back(word & 0x00FF);
}

void parse_mem(struct LSMData* p, uint8_t opcode, std::tuple<std::string, int16_t> tuple, YYLTYPE* loc) {
    // method to parse the instructions working with memory - identify operations
    if(!strcmp(std::get<0>(tuple).c_str(), "NONE")) {
        yyerror(loc, p, YY_("error: label does not exist."));
    }
    if(!strcmp(std::get<0>(tuple).c_str(), "TEXT")) {
        yyerror(loc, p, YY_("error: invalid label. Cannot load or store an address in the text segment."));
    }
    int16_t label = std::get<1>(tuple);
    if(!strcmp(std::get<0>(tuple).c_str(), "BSS")) {
        label += p -> data.size()/4;
    }

    p -> text.push_back(opcode);
    p -> text.push_back(label >> 8);
    p -> text.push_back(label & 0x00FF);
}

void parse_jump(struct LSMData* p, uint8_t opcode, std::tuple<std::string, int16_t> tuple, YYLTYPE* loc) {
    // method to parse the instructions working with jumps - identify operations
    if(!strcmp(std::get<0>(tuple).c_str(), "NONE")) {
        yyerror(loc, p, YY_("error: label does not exist."));
        p -> error_cnt++;
    }
    if(!strcmp(std::get<0>(tuple).c_str(), "DATA") || !strcmp(std::get<0>(tuple).c_str(), "BSS")) {
        yyerror(loc, p, YY_("error: invalid label. Cannot jump to a label in the data segment."));
        p -> error_cnt++;
    }

    int16_t label = std::get<1>(tuple) - p -> text.size();
    p -> text.push_back(opcode);
    p -> text.push_back(label >> 8);
    p -> text.push_back(label & 0x00FF);
}


void push_word(struct LSMData* p, uint32_t word){
    p -> data.push_back(word >> 24);
    p -> data.push_back((word >> 16) & 0x00FF);
    p -> data.push_back((word >> 8) & 0x00FF);
    p -> data.push_back(word & 0x00FF);
}
