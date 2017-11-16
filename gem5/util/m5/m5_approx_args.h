#ifndef M5_APPROX_ARGS
#define M5_APPROX_ARGS

#include "m5op.h"

void m5_DECLARE_APPROXIMATE_wrap(uint64_t addr, int row, int col, uint64_t apprLevel, size_t elemSize){
    uint64_t row_col = row;
    row_col = (row_col << 32) | (uint64_t)col;
    m5_DECLARE_APPROXIMATE(addr, row_col, apprLevel, elemSize);
}

void m5_UNDECLARE_APPROXIMATE_wrap(uint64_t addr){
    m5_UNDECLARE_APPROXIMATE(addr);
}

#endif // M5_APPROX_ARGS
