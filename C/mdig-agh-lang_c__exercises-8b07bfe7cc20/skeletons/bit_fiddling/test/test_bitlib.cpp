//#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" {
#include "bitlib.h"
}

#include <stdint.h>

TEST(BitlibTest, DecomposeIntoBytes) {
    uint8_t byte_hi, byte_lo;

    decompose_into_bytes(0x123B, &byte_hi, &byte_lo);

    EXPECT_EQ(byte_hi, 0x12);
    EXPECT_EQ(byte_lo, 0x3B);
}

TEST(BitlibTest, LastTwoBits) {
    EXPECT_EQ(last_two_bits(0x123B), 0x3);
}
