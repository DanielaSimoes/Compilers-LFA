#ifndef __S16_AST_ASSIGN_TO_VAR__
#define __S16_AST_ASSIGN_TO_VAR__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing an assignment to a scalar var
 */
class ASTAssignToVar : public ASTValue
{
private:
    std::string name;    ///< the target var
    ASTValue* value;       ///< the value

public:
    ASTAssignToVar(const char* n, int t, ASTValue* v)
        : name(n), value(v) { type = t; }

    ~ASTAssignToVar() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif

