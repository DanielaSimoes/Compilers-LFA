#include "astIf.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int ASTIf::gcnt = 0;

void ASTIf::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIf\n", 4*indent, "");
    indent++;
    cond->show(indent);
    then_block->show(indent);
    if (else_block) else_block->show(indent);
}

void ASTIf::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTIf\n");
    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }

    if (else_block)
    {
        string elsestart = "else_start_" + to_string(cnt);
        string elseend = "else_end_" + to_string(cnt);

        fprintf(fout, "ifeq %s\n", elsestart.c_str());
        then_block->generateLSM(fout);
        fprintf(fout, "goto %s\n", elseend.c_str());

        fprintf(fout, "%s:\n", elsestart.c_str());
        else_block->generateLSM(fout);

        fprintf(fout, "%s:\n", elseend.c_str());
    }
    else
    {
        string thenend = "then_end_" + to_string(cnt);

        fprintf(fout, "ifeq %s\n", thenend.c_str());
        then_block->generateLSM(fout);
        fprintf(fout, "%s:\n", thenend.c_str());
    }
}

////////////////////////////////////////////////////
