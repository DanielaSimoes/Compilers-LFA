#ifndef __S16_AST_IF__
#define __S16_AST_IF__

#include "astNode.h"
#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing an if instruction */
class ASTIf : public ASTNode
{
public:
    static int gcnt;
    int cnt;

private:
    ASTValue* cond;
    ASTNode* then_block; 
    ASTNode* else_block; ///< NULL if it isn't present

public:
    ASTIf(ASTValue* c, ASTNode* tb, ASTNode* eb) 
        : cond(c), then_block(tb), else_block(eb) { gcnt++; cnt = gcnt; }

    ~ASTIf() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
