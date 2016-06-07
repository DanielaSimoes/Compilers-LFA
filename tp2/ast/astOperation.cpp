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
    if(ASTNode::text == 0){
        fprintf(fout, ".text\n");
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
            fprintf(fout, "fadd\n");
        }else if(op == SUB){
            fprintf(fout, "fsub\n");
        }else if(op == MUL){
            fprintf(fout, "fmul\n");
        }else if( op == DIV){
            fprintf(fout, "fdiv\n");
        }else if( op == REM){
            fprintf(fout, "frem\n");
        }else if(op == NEG){
            fprintf(fout, "fneg\n");
        }
    }else if(getType() == ASTNode::INT){
        left->generateLSM(fout);
        fprintf(fout, "\n");
        right->generateLSM(fout);
        fprintf(fout, "\n");
        if(op == ADD){
            fprintf(fout, "iadd\n");
        }else if(op == SUB){
            fprintf(fout, "isub\n");
        }else if(op == MUL){
            fprintf(fout, "imul\n");
        }else if( op == DIV){
            fprintf(fout, "idiv\n");
        }else if( op == REM){
            fprintf(fout, "irem\n");
        }else if(op == NEG){
            fprintf(fout, "ineg\n");
        }
    }else if(getType() == ASTNode::BOOLEAN){
        if(op == AND){
            fprintf(fout, "iand\n");
        }else if(op == OR){
            fprintf(fout, "ior\n");
        }else if(op == XOR){
            fprintf(fout, "ixor\n");
        }else if(op == NOT){
            fprintf(fout, "ineg\n"); //NÃO TENHO A CERTEZA DISTO
        }

    }
}

////////////////////////////////////////////////////
