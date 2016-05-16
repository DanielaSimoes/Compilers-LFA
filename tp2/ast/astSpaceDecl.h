#ifndef __S16_AST_SPACE_DECL__
#define __S16_AST_SPACE_DECL__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing a space variable 
 * \details This node represents a variable to be 
 *      created in the .bss segment
 */
class ASTSpaceDecl : public ASTNode
{
private:
    std::string name;   ///< the name of the variable
    int size;           ///< its size in bytes

public:
    ASTSpaceDecl(const char* n, int sz) 
        : name(n), size(sz) {}

    ~ASTSpaceDecl() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
