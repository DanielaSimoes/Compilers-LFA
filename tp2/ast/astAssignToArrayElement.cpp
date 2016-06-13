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
    fprintf(fout, "%15s; assigning integer element value on array %s\n", " ", label.c_str());
    if (ASTNode::text == 0) {
        fprintf(fout, "%15s.text", " ");
        ASTNode::text = 1;
    }

    fprintf(fout, "\n%15sla %s\n", " ", label.c_str());
    offset->generateLSM(fout);
    value->generateLSM(fout);
    fprintf(fout, "%15siastore\n", " ");
    fprintf(fout, "\n");


    /*switch (entryPoint) {
        case 1:
            fprintf(fout, "%15sla %s\n", " ", label.c_str());
            fprintf(fout, "%15sipush %d\n", " ", offset);
            fprintf(fout, "%15sipush 2\n", " ");
            fprintf(fout, "%15sishl\n", " ");
            fprintf(fout, "%15siadd\n", " ");
            fprintf(fout, "%15sipush %d\n", " ", intValue);
            fprintf(fout, "%15siastore\n", " ");
            fprintf(fout, "\n");
            break;
        case 2:
            fprintf(fout, "%15sla %s\n", " ", label.c_str());
            fprintf(fout, "%15sipush %d\n", " ", offset);
            fprintf(fout, "%15sipush 2\n", " ");
            fprintf(fout, "%15sishl\n", " ");
            fprintf(fout, "%15siadd\n", " ");
            fprintf(fout, "%15sfpush %f\n", " ", floatValue);
            fprintf(fout, "%15sfastore\n", " ");
            fprintf(fout, "\n");
            break;
        case 3:
            if (type == INT) {
                fprintf(fout, "%15sla %s\n", " ", label.c_str());
                fprintf(fout, "%15sipush %d\n", " ", offset);
                fprintf(fout, "%15sipush 2\n", " ");
                fprintf(fout, "%15sishl\n", " ");
                fprintf(fout, "%15siadd\n", " ");
                idValue -> generateLSM(fout);
                fprintf(fout, "%15siastore\n", " ");
                fprintf(fout, "\n");
            } else if (type == FLOAT) {
                fprintf(fout, "%15sla %s\n", " ", label.c_str());
                fprintf(fout, "%15sipush %d\n", " ", offset);
                fprintf(fout, "%15sipush 2\n", " ");
                fprintf(fout, "%15sishl\n", " ");
                fprintf(fout, "%15siadd\n", " ");
                idValue -> generateLSM(fout);
                fprintf(fout, "%15sfastore\n", " ");
                fprintf(fout, "\n");
            }
            break;
        case 4:
            fprintf(fout, "%15sla %s\n", " ", label.c_str());
            offsetValue -> generateLSM(fout);
            fprintf(fout, "%15sipush 2\n", " ");
            fprintf(fout, "%15sishl\n", " ");
            fprintf(fout, "%15siadd\n", " ");
            fprintf(fout, "%15sipush %d\n", " ", intValue);
            fprintf(fout, "%15siastore\n", " ");
            fprintf(fout, "\n");
            break;
        case 5:
            fprintf(fout, "%15sla %s\n", " ", label.c_str());
            offsetValue -> generateLSM(fout);
            fprintf(fout, "%15sipush 2\n", " ");
            fprintf(fout, "%15sishl\n", " ");
            fprintf(fout, "%15siadd\n", " ");
            fprintf(fout, "%15sfpush %f\n", " ", floatValue);
            fprintf(fout, "%15sfastore\n", " ");
            fprintf(fout, "\n");
            break;
        case 6:
            if (type == INT) {
                fprintf(fout, "%15sla %s\n", " ", label.c_str());
                offsetValue -> generateLSM(fout);
                fprintf(fout, "%15sipush 2\n", " ");
                fprintf(fout, "%15sishl\n", " ");
                fprintf(fout, "%15siadd\n", " ");
                idValue -> generateLSM(fout);
                fprintf(fout, "%15siastore\n", " ");
                fprintf(fout, "\n");
            } else if (type == FLOAT) {
                fprintf(fout, "%15sla %s\n", " ", label.c_str());
                offsetValue -> generateLSM(fout);
                fprintf(fout, "%15sipush 2\n", " ");
                fprintf(fout, "%15sishl\n", " ");
                fprintf(fout, "%15siadd\n", " ");
                idValue -> generateLSM(fout);
                fprintf(fout, "%15sfastore\n", " ");
                fprintf(fout, "\n");
            }
            break;
    }*/
}

////////////////////////////////////////////////////
