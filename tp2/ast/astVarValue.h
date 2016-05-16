#ifndef __S16_AST_VAR_VALUE__
#define __S16_AST_VAR_VALUE__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing a variable value */
class ASTVarValue : public ASTValue
{
private:
    std::string name;

public:
    ASTVarValue(const char* n, int t)
        : name(n) { type = t; }

    ~ASTVarValue() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
