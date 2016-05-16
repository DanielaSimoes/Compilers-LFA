#ifndef __S16_AST_INTEGER_VALUE__
#define __S16_AST_INTEGER_VALUE__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTIntegerValue : public ASTValue
{
private:
    int32_t value;

public:
    ASTIntegerValue(int32_t v)
        : value(v) { type = INT; }

    ~ASTIntegerValue() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
