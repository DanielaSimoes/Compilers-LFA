#include "astCast.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTCast::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTCast\n", indent, "");
    indent++;
    opnd->show(indent);
}

void ASTCast::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTCast\n");
    //verificar função
    //verificar label em falta - deve ser criada com o

    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }

    opnd->generateLSM(fout);
    if(type == INT){
        fprintf(fout, "f2i\n");
    }else if(type == FLOAT){ // confirmar se FLOAT ou 3
        fprintf(fout, "i2f\n");
    }
    //fprintf(fout, "store\n");
    //opnd->generateLSM(fout);
}

////////////////////////////////////////////////////
