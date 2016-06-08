#ifndef __S16_AST_NODE__
#define __S16_AST_NODE__

#include <stdint.h>
#include <stdio.h>
#include <string>

using namespace std;

////////////////////////////////////////////////////

/** \brief The base class for all AST nodes */
class ASTNode
{
public:

    enum { NONE=0, TEXT, DATA };

    enum { BYTE, INT, FLOAT, BOOLEAN, STRING };

    enum { EQ, NE, LE, LT, GE, GT };

    enum { ADD, SUB, MUL, DIV, REM, NEG };

    enum { AND, OR, XOR, NOT };

    enum { READCHAR, READINT };

    enum { PRINTCHAR, PRINTINT };

    static int cur_segm;
    static int text;
    static bool init;
    static int cnt;

public:
    ASTNode() {}
    virtual ~ASTNode() {}

    /** show AST tree */
    virtual void show(uint32_t indent) = 0;

    /** Generate code for an if-then-else instruction */
    virtual void generateLSM(FILE* fout) = 0;
};

////////////////////////////////////////////////////

#endif
