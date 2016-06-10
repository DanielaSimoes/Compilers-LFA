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
    std::string name;       ///< the name of the variable
    std::string str;        // the string content

public:
    ASTStringDecl(const char* n, const char* s)
        : name(n), str(s) {}

    ~ASTStringDecl() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
