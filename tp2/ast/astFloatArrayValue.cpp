#include "astFloatArrayValue.h"
#include "astArrayHead.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTFloatArrayValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTFloatArrayValue\n", 4*indent, "");
}

void ASTFloatArrayValue::generateLSM(FILE* fout)
{
    if (ASTArrayHead::first)
    {
        ASTArrayHead::elems++;
        fprintf(fout, " %f", value);
        ASTArrayHead::first = false;
    }
    else if (ASTArrayHead::elems < ASTArrayHead::cur_size || ASTArrayHead::cur_size == -1) {
        ASTArrayHead::elems++;
        fprintf(fout, ", %f", value);
    }
}

////////////////////////////////////////////////////
