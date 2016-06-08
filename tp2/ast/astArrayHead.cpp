#include "astArrayHead.h"
#include "astIntegerArrayValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int32_t ASTArrayHead::cur_size = 0;

////////////////////////////////////////////////////

void ASTArrayHead::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTArrayHead\n", 4*indent, "");
}

void ASTArrayHead::generateLSM(FILE* fout)
{
    cur_size = size;
    ASTIntegerArrayValue::init = true;

    fprintf(stdout, "ASTArrayHead\n");
    fprintf(fout, "%s:\t .word", name.c_str());

    seq->generateLSM(fout);

    // if there aren't enough elements for the size specified
    if (ASTIntegerArrayValue::elems < cur_size) {
        while (ASTIntegerArrayValue::elems++ < cur_size && cur_size != NOT_DEFINED) {
            fprintf(fout, ", 0");
        }
    }

    // end declaration
    fprintf(fout, "\n");
    ASTIntegerArrayValue::elems = 0;
}

////////////////////////////////////////////////////
