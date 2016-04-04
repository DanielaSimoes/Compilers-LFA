#include "lbl-table.h"

#include <stdio.h>

void LabelTable::add(const char* label, void* value)
{
    // to be substituted by your code
    printf("assigning %p to %s\n", value, label);
}

void* LabelTable::getValue(const char* label)
{
    // to be substituted by your code
    printf("returning value of %s\n", label);
    return NULL;
}

