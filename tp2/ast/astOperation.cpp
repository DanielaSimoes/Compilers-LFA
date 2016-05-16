#include "astOperation.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTOperation::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTOperation\n", 4*indent, "");
    indent++;
    left->show(indent);
    right->show(indent);
}

void ASTOperation::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
