#ifndef __SYMTABLE__
#define __SYMTABLE__

#include <map>
#include <string>

using namespace std;

class SymTable
{
public:
    enum { 
        NONE=0, BYTE, INT, FLOAT, 
        INTARRAY, BYTEARRAY, FLOATARRAY,
        PROGRAM 
    };

    SymTable() {}
    ~SymTable() {}

    bool add(const char* key, int type);
    bool getType(const char* key, int* p_type);

private:
    map<string, int > table;
};

#endif
