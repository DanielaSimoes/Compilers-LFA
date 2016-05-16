#ifndef __S16_AST_FLOAT_DECL__
#define __S16_AST_FLOAT_DECL__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing a FLOAT declaration 
 */
class ASTFloatDecl : public ASTNode
{
private:
    std::string name;   ///< the name of the variable
    float value;       ///< its initial value

public:
    ASTFloatDecl(const char* n, float v) 
        : name(n), value(v) {}

    ~ASTFloatDecl() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
