#include "astIntDecl.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTIntDecl::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIntDecl\n", 4*indent, "");
}

void ASTIntDecl::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
