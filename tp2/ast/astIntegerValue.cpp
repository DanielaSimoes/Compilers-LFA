#include "astIntegerValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTIntegerValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTIntegerValue\n", 4*indent, "");
}

void ASTIntegerValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTIntegerValue\n");
    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "ipush %d\n", value);
}

////////////////////////////////////////////////////
