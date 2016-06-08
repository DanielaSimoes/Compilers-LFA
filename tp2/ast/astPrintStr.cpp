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
    fprintf(fout, "%15s; calling print string\n", " ");
    std::string variable = "s" + std::to_string(cnt);
    if (ASTNode::text || !init) {
        fprintf(fout, "%15s.data\n", " ");
        ASTNode::text = 0;
        init = true;
    }
    fprintf(fout, "%-14s .string %s\n", (variable + ":").c_str(), str.c_str());
    if (ASTNode::text == 0) {
        fprintf(fout, "%15s.text\n", " ");
        fprintf(fout, "L%d:\n", ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }
    fprintf(fout, "%15sla s%d\n", " ", cnt);
    fprintf(fout, "%15sjsr printStr\n", " ");
    // int i;
    // for (i = 1; i != str.length()-1; i++) {
    //     fprintf(fout, "%15sbipush '%c'\n", " ", str[i]);
    //     fprintf(fout, "%15swrite\n", " ");
    // }
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
