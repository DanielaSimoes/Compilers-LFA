#include "astSpaceDecl.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTSpaceDecl::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTSpaceDecl\n", 4*indent, "");
}

void ASTSpaceDecl::generateLSM(FILE* fout){
    fprintf(stdout, "ASTSpaceDecl\n");
    if(ASTNode::text || !init){
        fprintf(fout, ".data\n");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%s:\t .space %d\n", name.c_str(), size);
}

////////////////////////////////////////////////////
