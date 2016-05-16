#include "astAssignToVar.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTAssignToVar::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTAssignToVar\n", 4*indent, "");
    indent++;
    value->show(indent);
}

void ASTAssignToVar::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////

