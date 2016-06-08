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
    std::string name;   // array name
    int32_t size;       // array size
    ASTNode* seq;       // pointer to the head of the sequence of elems

public:
    static int32_t cur_size;// size of current array
    enum { NOT_DEFINED = -1 };

public:
    ASTArrayHead(const char* n, int32_t si, ASTNode* se)
        : name(n), size(si), seq(se) { type = INT; cur_size = size; }

    ~ASTArrayHead() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
