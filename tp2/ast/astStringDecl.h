#ifndef __S16_AST_STRING_DECL__
#define __S16_AST_STRING_DECL__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing a String declaration
 */
class ASTStringDecl : public ASTNode
{
private:
    std::string name;        ///< the name of the variable
    std::string value;       ///< its initial value

public:
    ASTStringDecl(const char* n, const char* v)
        : name(n), value(v) {}

    ~ASTStringDecl() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
