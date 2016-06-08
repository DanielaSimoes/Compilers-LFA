#ifndef __S16_AST_ARRAY_HEAD__
#define __S16_AST_ARRAY_HEAD__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTArrayHead : public ASTValue
{
private:
    std::string name;
    int32_t size;   // size specified
    int32_t elems;  // number of elements given
    ASTNode* seq;   // pointer to the head of the sequence of elems

public:
    ASTArrayHead(const char* n, int32_t si, ASTNode* se)
        : name(n), size(si), seq(se) { type = INT; elems = 0; }

    ~ASTArrayHead() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
