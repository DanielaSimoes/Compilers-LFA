#include "astFunctionCall.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTFunctionCall::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTFunctionCall\n", indent, "");
}

void ASTFunctionCall::generateLSM(FILE* fout){
    fprintf(stdout, "ASTFunctionCall\n");
    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    if(func_id==ASTNode::READCHAR)
        fprintf(fout, "read\n");
    else if(func_id==ASTNode::READINT){
        fprintf(fout, "read\n");
        fprintf(fout, "bipush\n");
    }
}

////////////////////////////////////////////////////
