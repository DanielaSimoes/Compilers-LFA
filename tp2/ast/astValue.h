#ifndef __S16_AST_VALUE__
#define __S16_AST_VALUE__

#include "astNode.h"

////////////////////////////////////////////////////

/** \brief The base class for all AST value nodes */
class ASTValue : public ASTNode
{
public:
    int type = -1;

public:
    ASTValue() {}
    virtual ~ASTValue() {}

    int getType() { return type; }
};

////////////////////////////////////////////////////

#endif
