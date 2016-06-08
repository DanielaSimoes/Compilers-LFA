#include "astArrayElementValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTArrayElementValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTArrayElementValue\n", 4*indent, "");
}

void ASTArrayElementValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTArrayElementValue\n");
    fprintf(fout, "%15s; accessing integer element value on array %s\n", " ", label.c_str());
    if (ASTNode::text == 0) {
        fprintf(fout, "%15s.text", " ")
        if (getType() == INT) {
            fprintf(fout, "%15sla %s\n", " ", label.c_str());
            fprintf(fout, "%15siadd %d\n", " ", offset);
            fprintf(fout, "%15siaload\n", " ");
            fprintf(fout, "\n");
        }
        ASTNode::text = 1;
    }
}

////////////////////////////////////////////////////
