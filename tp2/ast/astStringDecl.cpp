#include "astStringDecl.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTStringDecl::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTStringDecl\n", 4*indent, "");
}

void ASTStringDecl::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTStringDecl\n");
}

////////////////////////////////////////////////////
