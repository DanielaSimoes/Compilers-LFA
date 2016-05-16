#include "astExit.h"

#include <stdint.h>
#include <stdio.h>

#include "astLoop.h"

////////////////////////////////////////////////////

void ASTExit::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTExit\n", indent, "");
}

void ASTExit::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
