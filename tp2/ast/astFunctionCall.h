#ifndef __S16_AST_FUNCTION_CALL__
#define __S16_AST_FUNCTION_CALL__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a break instruction */
class ASTFunctionCall : public ASTValue
{
public:
    int func_id;

public:
    ASTFunctionCall(int id) : func_id(id) { type = ASTNode::INT; }

    ~ASTFunctionCall() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
