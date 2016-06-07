#include "astFloatDecl.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTFloatDecl::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTFloatDecl\n", 4*indent, "");
}

void ASTFloatDecl::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTFloatDecl\n");
    if(ASTNode::text || !init){
        fprintf(fout, ".data\n");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%s:\t .float %f\n", name.c_str(), value);

}

////////////////////////////////////////////////////
