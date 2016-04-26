#ifndef __LSM_LABEL_TABLE__
#define __LSM_LABEL_TABLE__

#include <map>
#include <tuple>
#include <string>
// #include "var-tuple.h"

class LabelTable {
public:

public:
    LabelTable() {}
    ~LabelTable() {}

    void add(const char* label, std::tuple<std::string, int16_t> varTuple);
    std::tuple<std::string, int16_t> getValue(std::string, const char* label);
    std::map<std::string, std::tuple<std::string, int16_t>> table;
    std::tuple<std::string, int16_t> varTuple;
};

#endif
