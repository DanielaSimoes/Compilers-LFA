#include "astFloatDecl.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTFloatDecl::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTFloatDecl\n", 4*indent, "");
}

void ASTFloatDecl::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
