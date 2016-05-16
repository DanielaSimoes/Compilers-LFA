#include "symtable.h"

#include <stdio.h>

using namespace std;

bool SymTable::add(const char* key, int type)
{
    printf("adding %s --> %d\n", key, type);
    return true;
}

bool SymTable::getType(const char* key, int* p_type)
{
    printf("geting %s\n", key);
    return true;
}

