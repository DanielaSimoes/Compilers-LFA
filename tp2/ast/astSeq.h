#ifndef __S16_AST_SEQ__
#define __S16_AST_SEQ__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a sequence of nodes
 */
class ASTSeq : public ASTNode
{
private:
    ASTNode *head, *tail;

public:
    ASTSeq(ASTNode* h, ASTNode* t)
        : head(h), tail(t) {}

    ~ASTSeq() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
