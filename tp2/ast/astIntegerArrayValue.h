#ifndef __S16_AST_INTEGER_ARRAY_VALUE__
#define __S16_AST_INTEGER_ARRAY_VALUE__

#include "astValue.h"
#include "astArrayHead.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTIntegerArrayValue : public ASTValue
{
private:
    int32_t value;

public:
    ASTIntegerArrayValue(int32_t v)
        : value(v) { type = INT; ASTArrayHead::elems++; }

    ~ASTIntegerArrayValue() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
