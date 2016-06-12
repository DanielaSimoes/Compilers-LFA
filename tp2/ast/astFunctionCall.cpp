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
    fprintf(fout, "%15s; calling a function\n", " ");
    if(ASTNode::text == 0){
        fprintf(fout, "%15s.text\n", " ");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    if(func_id==ASTNode::READCHAR)
        fprintf(fout, "%15sread\n", " ");
    else if(func_id==ASTNode::READINT){
        fprintf(fout, "%15sread\n", " ");
        fprintf(fout, "%15sbipush 0 \n", " ");
        fprintf(fout, "%15sisub\n", " ");
    }
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
