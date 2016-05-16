#ifndef __S16_AST_BREAK__
#define __S16_AST_BREAK__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a break instruction */
class ASTBreak : public ASTNode
{
public:
    ASTBreak() {}

    ~ASTBreak() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
