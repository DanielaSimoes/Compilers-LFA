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
    fprintf(fout, "%15s; declarating a float variable\n", " ");
    if(ASTNode::text || !init){
        fprintf(fout, "%15s.data\n", " ");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%-14s .float %f\n", (name + ":").c_str(), value);
    fprintf(fout, "\n");

}

////////////////////////////////////////////////////
