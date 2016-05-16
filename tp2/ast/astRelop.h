#ifndef __S16_AST_RELOP__
#define __S16_AST_RELOP__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a relational operation */
class ASTRelop : public ASTValue
{
public:
    static int gcnt;
    int cnt;
    
private:
    int op;             ///< The operator (one of EQ, NE, LT, LE, GT, GE)
    ASTValue* left;      ///< The left side operand
    ASTValue* right;     ///< The right side operand

public:
    ASTRelop(unsigned char o, ASTValue* l, ASTValue* r) 
        : op(o), left(l), right(r) 
    {
        type = BOOLEAN;
        gcnt++;
        cnt = gcnt;
    }

    ~ASTRelop() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
