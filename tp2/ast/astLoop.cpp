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
    if(loop_block) loop_block->show(indent);
}

void ASTLoop::generateLSM(FILE* fout)
{
    prev_scope = cur_scope;
    cur_scope = cnt;

    fprintf(stdout, "ASTLoop\n");
    fprintf(fout, "%15s; creating a loop\n", " ");
    if(ASTNode::text == 0){
        fprintf(fout, "%15s.text\n", " ");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }

    std::string labelstart = "LoopStart" + std::to_string(cnt);
    fprintf(fout, "%s\n", (labelstart + ":").c_str());
    //fprintf(fout, "prev_scope%d\n", ASTLoop::prev_scope);

    if(loop_block) loop_block->generateLSM(fout);

    // if !break
    fprintf(fout, "%15sgoto %s\n", " ", labelstart.c_str());
    std::string labelend = "LoopEnd" + std::to_string(cnt);
    fprintf(fout, "%s\n", (labelend + ":").c_str());
    fprintf(fout, "\n");
    cur_scope = prev_scope;
    //gcnt--;

    cur_scope = prev_scope;

}

////////////////////////////////////////////////////
