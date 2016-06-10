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
    int16_t offset;
    int intValue;
    float floatValue;
    ASTVarValue* idValue;
    ASTVarValue* offsetValue;
    int entryPoint;

public:
    ASTAssignToArrayElement(const char* l, int16_t o, int v)
        : label(l), offset(o), intValue(v) { type = INT; entryPoint = 1; }

    ASTAssignToArrayElement(const char* l, int16_t o, float v)
        : label(l), offset(o), floatValue(v) { type = FLOAT; entryPoint = 2; }

    ASTAssignToArrayElement(const char* l, int16_t o, ASTVarValue* v)
        : label(l), offset(o), idValue(v) { type = idValue -> getType(); entryPoint = 3; }

    ASTAssignToArrayElement(const char* l, ASTVarValue* o, int v)
        : label(l), intValue(v), offsetValue(o) { type = INT; entryPoint = 4; }

    ASTAssignToArrayElement(const char* l, ASTVarValue* o, float v)
        : label(l), floatValue(v), offsetValue(o) { type = FLOAT; entryPoint= 5; }

    ASTAssignToArrayElement(const char* l, ASTVarValue* o, ASTVarValue* v)
        : label(l), idValue(v), offsetValue(o) { type = idValue -> getType(); entryPoint = 6; }

    ~ASTAssignToArrayElement() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
