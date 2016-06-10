#ifndef __S16_AST_ASSIGN_TO_ARRAY_ELEMENT__
#define __S16_AST_ASSIGN_TO_ARRAY_ELEMENT__

#include "astValue.h"
#include "astVarValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a integer numeric constant */
class ASTAssignToArrayElement : public ASTValue {
private:
    std::string label;
    ASTValue* offset;
    ASTValue* value;

public:
    ASTAssignToArrayElement(const char* l, ASTValue* o, ASTValue* v)
        : label(l), offset(o), value(v) { }

    ~ASTAssignToArrayElement() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
