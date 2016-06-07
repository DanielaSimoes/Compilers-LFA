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
    fprintf(stdout, "ASTPrint\n");
    switch (proc_id) {
        case PRINTCHAR:
            fprintf(fout, "write\n");
            break;
        case PRINTINT:
            fprintf(fout, "jsr PrintInt\n");
        break;
    }
}

////////////////////////////////////////////////////
