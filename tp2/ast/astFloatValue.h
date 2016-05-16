#ifndef __S16_AST_FLOAT_VALUE__
#define __S16_AST_FLOAT_VALUE__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a float numeric constant */
class ASTFloatValue : public ASTValue
{
private:
    float value;

public:
    ASTFloatValue(int32_t v)
        : value(v) { type = FLOAT; }

    ~ASTFloatValue() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
