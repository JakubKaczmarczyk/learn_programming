//
// Created by kubak on 13.06.2022.
//

#include "gtest/gtest.h"
#include "catalogue.hpp"

TEST(ProductTest, create) {
Product product("RB01", "Robot", 10.2);

EXPECT_EQ(product.get_id(), "RB01");
EXPECT_EQ(product.get_name(), "Robot");
EXPECT_EQ(product.get_price(), 10.2);
}

TEST(ProductTest, to_strin) {
Product product("RB01", "Robot", 10.2);
EXPECT_EQ(to_string(product), "Robot [RB01] : $10.20");
}