#ifndef __S16_AST_CAST__
#define __S16_AST_CAST__

#include "astValue.h"

#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////

/** \brief A node representing a cast operation */
class ASTCast : public ASTValue
{
private:
    ASTValue* opnd;

public:
    ASTCast(int t, ASTValue* o) : opnd(o)
    { 
        type = t;
    }

    ~ASTCast() {}
    
    /** show AST tree */
    void show(uint32_t indent);

    /** Generate LSM code */
    void generateLSM(FILE* fout);
};

////////////////////////////////////////////////////

#endif
