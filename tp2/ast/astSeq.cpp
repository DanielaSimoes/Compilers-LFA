#include "astSeq.h"

#include <stdint.h>
#include <stdio.h>

void ASTSeq::show(uint32_t indent) {
    fprintf(stdout, ";%*s ASTSeq\n", 4*indent, "");
    indent++;
    if (head) head -> show(indent);
    if (tail) tail -> show(indent);
}


void ASTSeq::generateLSM(FILE* fout) {
    if (head) head -> generateLSM(fout);
    if (tail) tail -> generateLSM(fout);
}

////////////////////////////////////////////////////
