#include "astRelop.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int ASTRelop::gcnt = 0;

void ASTRelop::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTRelop\n", 4*indent, "");
    indent++;
    left->show(indent);
    right->show(indent);
}

void ASTRelop::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
