#ifndef __S16_AST_PRINT_STR__
#define __S16_AST_PRINT_STR__

#include "astNode.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

////////////////////////////////////////////////////

/** \brief A node representing a break instruction */
class ASTPrintStr : public ASTNode
{
public:
    static int gcnt;
    int cnt;
    std::string str;

public:
    ASTPrintStr(const char* s) : str(s) 
    {
        gcnt++;
        cnt = gcnt;
    }

    ~ASTPrintStr() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
