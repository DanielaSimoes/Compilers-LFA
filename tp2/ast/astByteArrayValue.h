#ifndef __S16_AST_BYTE_ARRAY_VALUE__
#define __S16_AST_BYTE_ARRAY_VALUE__

#include "astValue.h"
#include "astArrayHead.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTByteArrayValue : public ASTValue
{
private:
    unsigned int value;

public:
    ASTByteArrayValue(unsigned int v)
        : value(v) { type = BYTE; ASTArrayHead::elems++; }

    ~ASTByteArrayValue() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
