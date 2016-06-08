#ifndef __S16_AST_STRING_VALUE__
#define __S16_AST_STRING_VALUE__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTStringValue : public ASTValue
{
private:
    std::string value;

public:
    ASTStringValue(const char* v)
        : value(v) { type = STRING; }

    ~ASTStringValue() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
