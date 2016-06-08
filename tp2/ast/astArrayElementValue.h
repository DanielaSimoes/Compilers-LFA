#ifndef __S16_AST_ARRAY_ELEMENT_VALUE__
#define __S16_AST_ARRAY_ELEMENT_VALUE__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTArrayElementValue : public ASTValue {
private:
    int16_t offset;
    std::string label;

public:
    ASTArrayElementValue(const char* l, int16_t o)
        : label(l), offset(o) { type = INT; }

    ~ASTArrayElementValue() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
