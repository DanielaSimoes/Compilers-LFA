#include "astBreak.h"

#include <stdint.h>
#include <stdio.h>

#include "astLoop.h"

////////////////////////////////////////////////////

void ASTBreak::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTBreak\n", indent, "");
}

void ASTBreak::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
