#include "astIf.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int ASTIf::gcnt = 0;

void ASTIf::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIf\n", 4*indent, "");
    indent++;
    cond->show(indent);
    then_block->show(indent);
    if (else_block) else_block->show(indent);
}

void ASTIf::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
