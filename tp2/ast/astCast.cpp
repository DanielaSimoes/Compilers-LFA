#include "astCast.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTCast::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTCast\n", indent, "");
    indent++;
    opnd->show(indent);
}

void ASTCast::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
