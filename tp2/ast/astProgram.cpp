#include "astProgram.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

void ASTProgram::show(uint32_t indent) {
    fprintf(stdout, ";%*s ASTProgram:\n", 4*indent, "");
    indent++;
    program->show(indent);
}

void ASTProgram::generateLSM(FILE* fout) {
    fprintf(fout, "%15s.text\n", " ");
    fprintf(fout, "%s:\n", name.c_str());
    program -> generateLSM(fout);
}

////////////////////////////////////////////////////
