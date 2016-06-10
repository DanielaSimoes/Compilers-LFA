#include "astAssignToArrayElement.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTAssignToArrayElement::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTAssignToArrayElement\n", 4*indent, "");
}

void ASTAssignToArrayElement::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTAssignToArrayElement\n");
    fprintf(fout, "%15s; assigning integer element value on array %s\n", " ", label.c_str());
    if (ASTNode::text == 0) {
        fprintf(fout, "%15s.text", " ");
        if (getType() == INT) {
            fprintf(fout, "%15sla %s\n", " ", label.c_str());
            fprintf(fout, "%15siadd %d\n", " ", offset);
            fprintf(fout, "%15sipush %d\n", " ", value);
            fprintf(fout, "%15siastore\n", " ");
            fprintf(fout, "\n");
        } else if (getType() == FLOAT) {
            fprintf(fout, "%15sla %s\n", " ", label.c_str());
            fprintf(fout, "%15siadd %d\n", " ", offset);
            fprintf(fout, "%15sfpush %d\n", " ", value);
            fprintf(fout, "%15sfastore\n", " ");
            fprintf(fout, "\n");
        }
        ASTNode::text = 1;
    }
}

////////////////////////////////////////////////////
