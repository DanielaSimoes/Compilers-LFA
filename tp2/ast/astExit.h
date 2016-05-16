#ifndef __S16_AST_EXIT__
#define __S16_AST_EXIT__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a break instruction */
class ASTExit : public ASTNode
{
public:
    ASTExit() {}

    ~ASTExit() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
