#include "astIntDecl.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTIntDecl::show(uint32_t indent) {
    fprintf(stdout, ";%*s ASTIntDecl\n", 4*indent, "");
}

void ASTIntDecl::generateLSM(FILE* fout) {
    fprintf(stdout, "ASTIntDecl\n");
    fprintf(fout, "%15s; declarating a integer variable\n", " ");
    if (ASTNode::text || !init) {
        fprintf(fout, "%15s.data\n", " ");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%-14s .word %d\n", (name + ":").c_str(), value);
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
