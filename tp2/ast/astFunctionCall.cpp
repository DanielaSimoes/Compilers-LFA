#include "astFunctionCall.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTFunctionCall::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTFunctionCall\n", indent, "");
}

void ASTFunctionCall::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
