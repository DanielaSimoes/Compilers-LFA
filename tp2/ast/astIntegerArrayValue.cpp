#include "astIntegerArrayValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

bool ASTIntegerArrayValue::init = false;

void ASTIntegerArrayValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIntegerArrayValue\n", 4*indent, "");
}

void ASTIntegerArrayValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTIntegerArrayValue\n");
    if (!init) {
        fprintf(fout, " %d\n", value);
        init = true;
    }else {
        fprintf(fout, ", %d\n", value);
    }

}

////////////////////////////////////////////////////
