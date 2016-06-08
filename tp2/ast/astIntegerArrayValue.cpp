#include "astIntegerArrayValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

bool ASTIntegerArrayValue::init = true;

void ASTIntegerArrayValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIntegerArrayValue\n", 4*indent, "");
}

void ASTIntegerArrayValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTIntegerArrayValue\n");
    if (init) {
        fprintf(fout, " %d", value);
        init = false;
    }else {
        fprintf(fout, ", %d", value);
    }

}

////////////////////////////////////////////////////
