#include "astLoop.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int ASTLoop::gcnt = 0;
int ASTLoop::cur_scope = 0;

void ASTLoop::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTLoop\n", 4*indent, "");
    indent++;
    loop_block->show(indent);
}

void ASTLoop::generateLSM(FILE* fout)
{
}

////////////////////////////////////////////////////

