#include "astArrayHead.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTArrayHead::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTArrayHead\n", 4*indent, "");
}

void ASTArrayHead::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTArrayHead\n");
    fprintf(fout, ".word");
}

////////////////////////////////////////////////////
