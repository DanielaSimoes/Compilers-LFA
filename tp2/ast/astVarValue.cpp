#include "astVarValue.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTVarValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTVarValue\n", 4*indent, "");
}

void ASTVarValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTVarValue\n");
    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "load %s\n", name.c_str());
    //fprintf(fout, "write\n");
}

////////////////////////////////////////////////////
