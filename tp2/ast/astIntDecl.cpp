#include "astIntDecl.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTIntDecl::show(uint32_t indent) {
    fprintf(stdout, ";%*s ASTIntDecl\n", 4*indent, "");
}

void ASTIntDecl::generateLSM(FILE* fout) {
    fprintf(stdout, "ASTIntDecl\n");
    if (ASTNode::text || !init) {
        fprintf(fout, ".data\n");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%s:\t .word %d\n", name.c_str(), value);
}

////////////////////////////////////////////////////
