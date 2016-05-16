#ifndef __S16_AST_PRINT__
#define __S16_AST_PRINT__

#include "astNode.h"
#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a break instruction */
class ASTPrint : public ASTNode
{
public:
    ASTValue* value;
    int proc_id;

public:
    ASTPrint(int i, ASTValue* v) : value(v), proc_id(i)
    {
        proc_id = i;
    }

    ~ASTPrint() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
