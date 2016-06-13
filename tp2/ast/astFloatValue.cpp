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
    fprintf(fout, "%15s; designating a float value\n", " ");
    if(ASTNode::text == 0){
        fprintf(fout, "%15s.text\n", " ");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "%15sfpush %f\n", " ", value);
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
