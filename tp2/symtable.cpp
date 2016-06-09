#include "symtable.h"

#include <stdio.h>

using namespace std;

bool SymTable::add(const char* key, int type)
{
    if (!table[std::string(key)]) {
        table[std::string(key)] = type;
        return true;
    }

    return false;
}

bool SymTable::getType(const char* key, int* p_type)
{
    if (table[std::string(key)] != NONE) {
        *p_type = table[std::string(key)];
        return true;
    }

    return false;
}
