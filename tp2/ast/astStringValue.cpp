#include "astStringValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTStringValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTStringValue\n", 4*indent, "");
}

void ASTStringValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTStringValue\n");
}

////////////////////////////////////////////////////
