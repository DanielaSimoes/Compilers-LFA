#ifndef __S16_AST_INT_DECL__
#define __S16_AST_INT_DECL__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing an INT declaration
 */
class ASTIntDecl : public ASTNode
{
private:
    std::string name;   ///< the name of the variable
    int32_t value;      ///< its initial value

public:
    ASTIntDecl(const char* n, int32_t v) 
        : name(n), value(v) {}

    ~ASTIntDecl() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
