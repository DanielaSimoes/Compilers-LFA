#include "astByteArrayValue.h"
#include "astArrayHead.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTByteArrayValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTByteArrayValue\n", 4*indent, "");
}

void ASTByteArrayValue::generateLSM(FILE* fout)
{
    fprintf(stdout, "ASTByteArrayValue\n");
    if (ASTArrayHead::first)
    {
        ASTArrayHead::elems++;
        fprintf(fout, " %c", value);
        ASTArrayHead::first = false;
    }
    else if (ASTArrayHead::elems < ASTArrayHead::cur_size || ASTArrayHead::cur_size == -1) {
        ASTArrayHead::elems++;
        fprintf(fout, ", %d", value);
        printf("%d\n", value);
    }
}

////////////////////////////////////////////////////
