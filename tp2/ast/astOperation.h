#ifndef __S16_AST_OPERATION__
#define __S16_AST_OPERATION__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing an aritmetic or  operation */
class ASTOperation : public ASTValue
{
private:
    int op;             ///< The operator (one of )
    ASTValue* left;      ///< The left side operand
    ASTValue* right;     ///< The right side operand

public:
    ASTOperation(unsigned char o, ASTValue* l, ASTValue* r)
        : op(o), left(l), right(r) 
    {
        type = -1;
        if (left == NULL)
        {
            if (right != NULL) type = right->getType();
        }
        else if (right == NULL)
        {
            type = left->getType();
        }
        else
        {
            int t1 = left->getType();
            int t2 = right->getType();
            type = (t1 == t2) ? t1 : FLOAT;
        }
    }

    ~ASTOperation() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
