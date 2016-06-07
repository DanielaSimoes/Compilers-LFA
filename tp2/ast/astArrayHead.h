#ifndef __S16_AST_ARRAY_HEAD__
#define __S16_AST_ARRAY_HEAD__

#include "astValue.h"
#include "astIntegerArrayValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTArrayHead : public ASTValue
{
private:
    int32_t size;
    ASTIntegerArrayValue *first;

public:
    ASTArrayHead(int32_t s, ASTIntegerArrayValue* f)
        : size(s), first(f) { type = INT; }

    ~ASTArrayHead() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
