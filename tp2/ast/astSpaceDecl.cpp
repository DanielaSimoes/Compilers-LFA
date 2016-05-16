#include "astSpaceDecl.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTSpaceDecl::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTSpaceDecl\n", 4*indent, "");
}

void ASTSpaceDecl::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
