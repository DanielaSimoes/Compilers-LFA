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
    int16_t size;       ///< its initial value

public:
    ASTStringDecl(const char* n, int16_t s)
        : name(n), size(s) {}

    ~ASTStringDecl() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
