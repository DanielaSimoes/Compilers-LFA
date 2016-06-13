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
    fprintf(fout, "%15s; checking solution for relation (RELOP)\n", " ");
    int leftType = left -> getType();
    int rightType = right -> getType();
    bool floatComparison = leftType == FLOAT && rightType == FLOAT;
    left -> generateLSM(fout);      // este gera elemento A na stack
    if(ASTNode::text == 0){
        fprintf(fout, "%15s.text\n", " ");
        ASTNode::text = 1;
    }
    if (leftType == INT && rightType == FLOAT) {
        fprintf(fout, "%15si2f\n", " ");     // se for comparação com reais, inteiro A passa para real A
        floatComparison = true;
    }
    right -> generateLSM(fout);     // este gera elemento B na stack
    if(ASTNode::text == 0){
        fprintf(fout, "%15s.text\n", " ");
        ASTNode::text = 1;
    }
    if (leftType == FLOAT && rightType == INT) {
        fprintf(fout, "%15si2f\n", " ");     // se for comparação com reais, inteiro B passa para real B
        floatComparison = true;
    }
    // na stack temos B em cima de A
    if (ASTNode::text == 0) {
        fprintf(fout, "%15s.text\n", " ");
        ASTNode::text = 1;
    }
    std::string variable = "relop" + std::to_string(cnt);
    if (floatComparison) {
        fprintf(fout, "%15sfcmpg\n", " ");
        switch (op) {
            case EQ:
                fprintf(fout, "%15sifeq %s\n", " ", (variable + "_true").c_str());
                break;
            case NE:
                fprintf(fout, "%15sifne %s\n", " ", (variable + "_true").c_str());
                break;
            case LT:
                fprintf(fout, "%15sipush -1\n", " ");
                fprintf(fout, "%15sisub\n", " ");
                fprintf(fout, "%15sifeq %s\n", " ", (variable + "_true").c_str());
                break;
            case GT:
                fprintf(fout, "%15sipush 1\n", " ");
                fprintf(fout, "%15sisub\n", " ");
                fprintf(fout, "%15sifeq %s\n", " ", (variable + "_true").c_str());
                break;
            case LE:
                fprintf(fout, "%15sifle %s\n", " ", (variable + "_true").c_str());
                break;
            case GE:
                fprintf(fout, "%15sifge %s\n", " ", (variable + "_true").c_str());
                break;
        }
    } else if (leftType == INT && rightType == INT) {
        fprintf(fout, "%15sisub\n", " ");
        if (op == EQ) {
            fprintf(fout, "%15sifeq %s\n", " ", (variable + "_true").c_str());
        } else if (op == NE) {
            fprintf(fout, "%15sifne %s\n", " ", (variable + "_true").c_str());
        } else if (op == LT) {
            fprintf(fout, "%15siflt %s\n", " ", (variable + "_true").c_str());
        } else if ( op == LE) {
            fprintf(fout, "%15sifle %s\n", " ", (variable + "_true").c_str());
        } else if (op == GT) {
            fprintf(fout, "%15sifgt %s\n", " ", (variable + "_true").c_str());
        } else if (op == GE) {
            fprintf(fout, "%15sifge %s\n", " ", (variable + "_true").c_str());
        }
    }

    fprintf(fout, "%s:\n", (variable + "_false").c_str());
    fprintf(fout, "%15sipush 0\n", " ");
    fprintf(fout, "%15sgoto %s\n", " ", (variable + "_end").c_str());
    fprintf(fout, "%s:\n", (variable + "_true").c_str());
    fprintf(fout, "%15sipush 1\n", " ");
    fprintf(fout, "%s:\n", (variable + "_end").c_str());
}

////////////////////////////////////////////////////
