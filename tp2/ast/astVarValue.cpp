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
    fprintf(fout, "%15s; checking value of variable\n", " ");
    if(ASTNode::text == 0){
        fprintf(fout, "%15s.text\n", " ");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "%15sload %s\n", " ", name.c_str());
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
