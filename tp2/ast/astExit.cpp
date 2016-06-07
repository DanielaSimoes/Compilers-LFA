#include "astExit.h"

#include <stdint.h>
#include <stdio.h>

#include "astLoop.h"

////////////////////////////////////////////////////

void ASTExit::show(uint32_t indent) {
    fprintf(stdout, ";%*s ASTExit\n", indent, "");
}

void ASTExit::generateLSM(FILE* fout) {
    fprintf(stdout, "ASTExit\n");
    if (ASTNode::text == 0) {
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n", ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "halt\n");
}

////////////////////////////////////////////////////
