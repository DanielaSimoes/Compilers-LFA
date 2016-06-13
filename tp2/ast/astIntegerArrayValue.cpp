#include "astIntegerArrayValue.h"
#include "astArrayHead.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTIntegerArrayValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIntegerArrayValue\n", 4*indent, "");
}

void ASTIntegerArrayValue::generateLSM(FILE* fout)
{
    if (ASTArrayHead::first)
    {
        ASTArrayHead::elems++;
        fprintf(fout, " %d", value);
        ASTArrayHead::first = false;
    }
    else if (ASTArrayHead::elems < ASTArrayHead::cur_size || ASTArrayHead::cur_size == -1) {
        ASTArrayHead::elems++;
        fprintf(fout, ", %d", value);
    }
}

////////////////////////////////////////////////////
