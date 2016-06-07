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
    fprintf(stdout, "ASTBreak\n");
    if (ASTLoop::gcnt)
        //ASTLoop::cur_scope= ASTLoop::cur_scope+1;

        //fprintf(fout, "curr_scope%d\n", ASTLoop::cur_scope);
        fprintf(fout, "goto LoopEnd%s\n", std::to_string(ASTLoop::cur_scope).c_str());

}

////////////////////////////////////////////////////
