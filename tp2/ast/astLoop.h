#ifndef __S16_AST_LOOP__
#define __S16_AST_LOOP__

#include "astNode.h"

#include <stdint.h>
#include <stdint.h>
#include <string>
#include <vector>

////////////////////////////////////////////////////

/** \brief A node representing a loop instruction */
class ASTLoop : public ASTNode
{
public:
    static int gcnt;
    static int cur_scope;
    int cnt;
    int prev_scope;

private:
    ASTNode* loop_block; 

public:
    ASTLoop(ASTNode* lb) : loop_block(lb)
    { 
        gcnt++; 
        cnt = gcnt;
        prev_scope = cur_scope;
        cur_scope = cnt;
    }

    ~ASTLoop()
    {
        cur_scope = prev_scope;
    }

    /** show AST tree */
    void show(uint32_t indent);

    /** Generate code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
