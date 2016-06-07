#include "astAssignToVar.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTAssignToVar::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTAssignToVar\n", 4*indent, "");
    indent++;
    value->show(indent);
}

void ASTAssignToVar::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTAssignToVar\n");
    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    value->generateLSM(fout);
    fprintf(fout, "\n");
    fprintf(fout, "store %s\n", name.c_str());
}

////////////////////////////////////////////////////
