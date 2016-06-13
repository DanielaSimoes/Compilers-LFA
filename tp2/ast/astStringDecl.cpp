#include "astStringDecl.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTStringDecl::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTStringDecl\n", 4*indent, "");
}

void ASTStringDecl::generateLSM(FILE* fout) {
    fprintf(fout, "%15s; declarating a string variable\n", " ");
    if (ASTNode::text || !init) {
        fprintf(fout, "%15s.data\n", " ");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%-14s .string %s\n", (name + ":").c_str(), str.c_str());
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
