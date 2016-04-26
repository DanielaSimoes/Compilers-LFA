#include "lbl-table.h"
#include <stdio.h>
#include <tuple>
#include <string.h>

void LabelTable::add(const char* label, std::tuple<std::string, int16_t> varTuple)
{
    table[std::string(label)] = varTuple;
}

std::tuple<std::string, int16_t> LabelTable::getValue(std::string type, const char* label)
{
    const char* tmp = "";
    std::tuple<std::string, int16_t> tuple = table[std::string(label)];
    if (!strcmp(std::get<0>(tuple).c_str(),tmp)) {
        std::tuple<std::string, int16_t> toReturn ("NONE",0);
        return toReturn;
    }

    return tuple;
}
