#include "astIntegerArrayValue.h"
#include "astArrayHead.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int32_t ASTIntegerArrayValue::elems = 0;
bool ASTIntegerArrayValue::init = true;

////////////////////////////////////////////////////

void ASTIntegerArrayValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIntegerArrayValue\n", 4*indent, "");
}

void ASTIntegerArrayValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTIntegerArrayValue\n");
    if (init)
    {
        fprintf(fout, " %d", value);
        init = false;
    }
    else if (elems < ASTArrayHead::cur_size || ASTArrayHead::cur_size == -1) {
        elems++;
        fprintf(fout, ", %d", value);
    }
}

////////////////////////////////////////////////////
