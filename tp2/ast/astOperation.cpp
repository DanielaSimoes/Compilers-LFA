#include "astOperation.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTOperation::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTOperation\n", 4*indent, "");
    indent++;
    if (left) left->show(indent);
    if (right) right->show(indent);
}

void ASTOperation::generateLSM(FILE* fout){

    fprintf(stdout, "ASTOperation\n");
    fprintf(fout, "%15s; creating an operation\n", " ");
    if(ASTNode::text == 0){
        fprintf(fout, "%15s.text\n", " ");
        fprintf(fout, "L%d:\n",ASTNode::cnt);
        ASTNode::cnt++;
        ASTNode::text = 1;
    }

    if(getType() == ASTNode::FLOAT){

        left->generateLSM(fout);
        fprintf(fout, "\n");
        right->generateLSM(fout);
        fprintf(fout, "\n");
        if(op == ADD){
            fprintf(fout, "%15sfadd\n", " ");
        }else if(op == SUB){
            fprintf(fout, "%15sfsub\n", " ");
        }else if(op == MUL){
            fprintf(fout, "%15sfmul\n", " ");
        }else if( op == DIV){
            fprintf(fout, "%15sfdiv\n", " ");
        }else if( op == REM){
            fprintf(fout, "%15sfrem\n", " ");
        }else if(op == NEG){
            fprintf(fout, "%15sfneg\n", " ");
        }
    }else if(getType() == ASTNode::INT){
        left->generateLSM(fout);
        fprintf(fout, "\n");
        right->generateLSM(fout);
        fprintf(fout, "\n");
        if(op == ADD){
            fprintf(fout, "%15siadd\n", " ");
        }else if(op == SUB){
            fprintf(fout, "%15sisub\n", " ");
        }else if(op == MUL){
            fprintf(fout, "%15simul\n", " ");
        }else if( op == DIV){
            fprintf(fout, "%15sidiv\n", " ");
        }else if( op == REM){
            fprintf(fout, "%15sirem\n", " ");
        }else if(op == NEG){
            fprintf(fout, "%15sineg\n", " ");
        }
    }else if(getType() == ASTNode::BOOLEAN){
        if(op == AND){
            fprintf(fout, "%15siand\n", " ");
        }else if(op == OR){
            fprintf(fout, "%15sior\n", " ");
        }else if(op == XOR){
            fprintf(fout, "%15sixor\n", " ");
        }else if(op == NOT){
            fprintf(fout, "%15sineg\n", " ");
        }
    }
    fprintf(fout, "\n");
}

////////////////////////////////////////////////////
