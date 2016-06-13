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
    fprintf(fout, "%15s; breaking a loop\n", " ");
    if (ASTLoop::gcnt)
        fprintf(fout, "%15sgoto LoopEnd%s\n", " ",  std::to_string(ASTLoop::cur_scope).c_str());
    fprintf(fout, "\n");

}

////////////////////////////////////////////////////
