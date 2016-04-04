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

