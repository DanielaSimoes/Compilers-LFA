#ifndef __LSM_DATA__
#define __LSM_DATA__

#include "lsm-lexer.h"
#include "lbl-table.h"
#include <vector>
#include <stdint.h>

typedef struct LSMData
{
    yyscan_t scanner;           // lexer info
    LabelTable* lbl_table;      // pointer to labels' symbol table
    std::vector<uint8_t> text;  // vector of opcodes
    std::vector<uint8_t> data;  // vector of variables
    uint16_t bss_size;          // size of non-initializaed variables
    uint16_t text_size;         // size of text segment
    bool syntax_only;           // if true, does not generate code
    int error_cnt;              // number of parsing errors
    bool first_time;            // control if parsing is in first or second scan

} LSMData;

#endif
