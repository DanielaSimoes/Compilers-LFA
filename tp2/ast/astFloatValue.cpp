#include "astFloatValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTFloatValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTFloatValue\n", 4*indent, "");
}

void ASTFloatValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTValue\n");
    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "fpush %f\n", value);
}

////////////////////////////////////////////////////
