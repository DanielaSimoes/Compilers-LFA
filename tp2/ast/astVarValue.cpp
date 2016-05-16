#include "astVarValue.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTVarValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTVarValue\n", 4*indent, "");
}

void ASTVarValue::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
