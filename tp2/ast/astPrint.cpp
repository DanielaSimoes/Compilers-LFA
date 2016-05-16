#include "astPrint.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTPrint::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTPrint\n", 4*indent, "");
}

void ASTPrint::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
