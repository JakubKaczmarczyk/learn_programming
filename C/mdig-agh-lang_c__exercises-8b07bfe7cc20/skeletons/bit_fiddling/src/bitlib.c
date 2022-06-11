#include "bitlib.h"

void decompose_into_bytes(const uint16_t val, uint8_t* byte_hi, uint8_t* byte_lo) {
    *byte_hi = (uint8_t) (val >> 8U);
    *byte_lo = (uint8_t) val;
}

extern int last_two_bits(int val) {
    return (int) ((uint8_t) val & (uint8_t) 3);
}
