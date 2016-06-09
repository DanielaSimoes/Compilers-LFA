#include "astStringValue.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

void ASTStringValue::show(uint32_t indent)
{
    fprintf(stdout, ";%*s ASTStringValue\n", 4*indent, "");
}

void ASTStringValue::generateLSM(FILE* fout) {
    fprintf(stdout, "ASTStringValue\n");
    fprintf(fout, "%15s; designating a string value\n", " ");
    if (ASTNode::text == 1) {
        fprintf(fout, "%15s.data\n", " ");
        ASTNode::text = 0;
    }
    // value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());//std::replace(value.begin(), value.end(), '\"', '\0'));
    // std::remove(str.begin(), str.end(), chars[i]), str.end()
    fprintf(fout, "%-14s .string %s\n", ("str" + to_string(ASTNode::cnt++) + ":").c_str(), value.c_str());
    if (ASTNode::text == 0) {
        fprintf(fout, "%15s.text\n", " ");
        ASTNode::text = 1;
    }
    fprintf(fout, "%15sla %s\n", " ", ("str" + to_string(ASTNode::cnt-1)).c_str());
    // fprintf(fout, "\n");
}

// void removeCharsFromString( string &str, char* charsToRemove ) {
//    for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
//       str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
//    }
// }

////////////////////////////////////////////////////
