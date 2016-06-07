#include "astRelop.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int ASTRelop::gcnt = 0;

void ASTRelop::show(uint32_t indent) {
    fprintf(stdout, ";%*s ASTRelop\n", 4*indent, "");
    indent++;
    left -> show(indent);
    right -> show(indent);
}

void ASTRelop::generateLSM(FILE* fout) {
    fprintf(stdout, "ASTRelop\n");
    int leftType = left -> getType();
    int rightType = right -> getType();
    bool floatComparison = leftType == FLOAT && rightType == FLOAT;
    left -> generateLSM(fout);      // este gera elemento A na stack
    if (leftType == INT && rightType == FLOAT) {
        fprintf(fout, "i2f\n");     // se for comparação com reais, inteiro A passa para real A
        floatComparison = true;
    }
    right -> generateLSM(fout);     // este gera elemento B na stack
    if (leftType == FLOAT && rightType == INT) {
        fprintf(fout, "i2f\n");     // se for comparação com reais, inteiro B passa para real B
        floatComparison = true;
    }
    // na stack temos B em cima de A
    if (ASTNode::text == 0) {
        fprintf(fout, ".text\n");
        ASTNode::text = 1;
    }
    std::string variable = "R" + std::to_string(cnt);
    if (floatComparison) {
        fprintf(fout, "fcmpg\n");
    } else if (leftType == INT && rightType == INT) {
        fprintf(fout, "isub\n");
        if (op == EQ) {
            fprintf(fout, "ifeq %s\n", variable.c_str());
        } else if (op == NE) {
            fprintf(fout, "ifne %s\n", variable.c_str());
        } else if (op == LT) {
            fprintf(fout, "iflt %s\n", variable.c_str());
        } else if ( op == LE) {
            fprintf(fout, "ifle %s\n", variable.c_str());
        } else if (op == GT) {
            fprintf(fout, "ifgt %s\n", variable.c_str());
        } else if (op == GE) {
            fprintf(fout, "ifge %s\n", variable.c_str());
        }
    }
}

////////////////////////////////////////////////////
