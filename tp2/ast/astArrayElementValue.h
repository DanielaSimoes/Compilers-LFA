#ifndef __S16_AST_ARRAY_ELEMENT_VALUE__
#define __S16_AST_ARRAY_ELEMENT_VALUE__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTArrayElementValue : public ASTValue {
private:
    std::string label;
    ASTValue* value;

public:
    ASTArrayElementValue(int t, const char* l, ASTValue* v)
        : label(l), value(v) { type = t; }

    ~ASTArrayElementValue() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
