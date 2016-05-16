#include "astPrintStr.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

int ASTPrintStr::gcnt = 0;

void ASTPrintStr::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTPrintStr\n", indent, "");
}

void ASTPrintStr::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////
