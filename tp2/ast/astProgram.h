#ifndef __S16_AST_PROGRAM__
#define __S16_AST_PROGRAM__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing an S16 program */
class ASTProgram : public ASTNode
{
private:
    std::string name;       ///< name of the program
    ASTNode* program;        ///< the program outer block

public:
    ASTProgram(const char* nm, ASTNode* bl) 
        : name(nm), program(bl) {}

    ~ASTProgram() {}

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
