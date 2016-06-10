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
    fprintf(fout, "%15s; accessing element value on array %s\n", " ", label.c_str());
    if (ASTNode::text == 0) {
        fprintf(fout, "%15s.text", " ");
        ASTNode::text = 1;
    }

    if (type == INT || type == STRING) {
        fprintf(fout, "%15sla %s\n", " ", label.c_str());
        value->generateLSM(fout);
        fprintf(fout, "%15siaload\n", " ");
        fprintf(fout, "\n");
    } else if (type == FLOAT) {
        fprintf(fout, "%15sla %s\n", " ", label.c_str());
        value->generateLSM(fout);
        fprintf(fout, "%15sfaload\n", " ");
        fprintf(fout, "\n");
    }
}

////////////////////////////////////////////////////
