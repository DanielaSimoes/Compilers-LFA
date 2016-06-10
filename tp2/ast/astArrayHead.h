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
    static int32_t elems;   // number of elements already given
    static bool first;       // tell if it is being written the first elem
    enum { NOT_DEFINED = -1 };

public:
    ASTArrayHead(int t, const char* n, int32_t si, ASTNode* se)
        : name(n), size(si), seq(se) {type = t; cur_size = size; }

    ~ASTArrayHead() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
