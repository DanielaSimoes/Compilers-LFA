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
    fprintf(fout, "%15s; calling print\n", " ");
    switch (proc_id) {
        case PRINTCHAR:
            fprintf(fout, "%15swrite\n", " ");
            break;
        case PRINTINT:
            value->generateLSM(fout);
            fprintf(fout, "%15sjsr printInt\n", " ");
            break;
    }
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
