#include "astArrayHead.h"
#include "astIntegerArrayValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

int32_t ASTArrayHead::cur_size = 0;
int32_t ASTArrayHead::elems = 0;
bool ASTArrayHead::first = true;

////////////////////////////////////////////////////

void ASTArrayHead::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTArrayHead\n", 4*indent, "");
}

void ASTArrayHead::generateLSM(FILE* fout)
{
    fprintf(fout, "%15s; creating an array\n", " ");
    if(ASTNode::text || !init){
        fprintf(fout, "%15s.data\n", " ");
        ASTNode::text = 0;
        init = true;
    }

    cur_size = size;
    first = true;

    if (type == ASTNode::INT)
        fprintf(fout, "%-14s .word ", (name + ":").c_str());
    else if (type == ASTNode::FLOAT)
        fprintf(fout, "%-14s .float ", (name + ":").c_str());
    else if (type == ASTNode::BYTE)
        fprintf(fout, "%-14s .byte ", (name + ":").c_str());

    seq->generateLSM(fout);

    // if there aren't enough elements for the size specified
    if (elems < cur_size) {
        while (elems++ < cur_size && cur_size != NOT_DEFINED) {
            fprintf(fout, ", 0");
        }
    }

    // end declaration
    fprintf(fout, "\n");
    elems = 0;
}

////////////////////////////////////////////////////
