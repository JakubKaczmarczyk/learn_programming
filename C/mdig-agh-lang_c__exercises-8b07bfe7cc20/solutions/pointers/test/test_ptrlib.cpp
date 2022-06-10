//#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" {
#include "ptrlib.h"
}

TEST(BitlibTest, DecomposeIntoBytes) {
    int a = 1;
    int b = 2;

    swap(&a, &b);

    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);
}
