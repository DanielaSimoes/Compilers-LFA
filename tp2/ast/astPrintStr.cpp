#include "astPrintStr.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////

int ASTPrintStr::gcnt = 0;

void ASTPrintStr::show(uint32_t indent) {
    fprintf(stdout, ";%*s ASTPrintStr\n", indent, "");
}

void ASTPrintStr::generateLSM(FILE* fout) {
    fprintf(stdout, "ASTPrintStr\n");
    std::string variable = "s" + std::to_string(cnt);
    if (ASTNode::text || !init) {
        fprintf(fout, ".data\n");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%s:\t.string %s\n", variable.c_str(), str.c_str());
    if (ASTNode::text == 0) {
        fprintf(fout, ".text\n");
        fprintf(fout, "L%d:\n", ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "la s%d\n", cnt);
    fprintf(fout, "jsr printStr\n");
    int i;
    for (i = 0; i != str.length(); i++) {
        fprintf(fout, "bipush '%c'\n", str[i]);
        fprintf(fout, "write\n");
    }
}

////////////////////////////////////////////////////
