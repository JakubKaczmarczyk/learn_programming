//
// Created by kubak on 13.06.2022.
//
#include "gtest/gtest.h"
#include "catalogue.hpp"

TEST(CatalogueTest, containsKeyIsNotPresent) {
    Catalogue catalogue;
    Product p("0", "robot", 2.0);
    catalogue.add_product(p);
    EXPECT_EQ(catalogue.contains("1"), false);
}

TEST(CatalogueTest, containsKeyIsPresent) {
    Catalogue catalogue;
    Product p1("0", "robot", 2.0);
    Product p2("1", "robot2", 2.0);
    catalogue.add_product(p1);
    catalogue.add_product(p2);
    EXPECT_EQ(catalogue.contains("1"), true);
}