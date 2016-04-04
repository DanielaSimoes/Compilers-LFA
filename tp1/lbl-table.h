#ifndef __LSM_LABEL_TABLE__
#define __LSM_LABEL_TABLE__

#include <map>
#include <string>

class LabelTable
{
public:
    
public:
    LabelTable() {}
    ~LabelTable() {}

    void add(const char* label, void* value);
    void* getValue(const char* label);

private:
    std::map<std::string, void*> table;
};

#endif
