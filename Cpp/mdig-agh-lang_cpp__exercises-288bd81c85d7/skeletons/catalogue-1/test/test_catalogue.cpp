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

TEST(CatalogueTest, getProductsWithAppropriatePrice) {
    Product p1("X1", "Toy X1", 10.3);
    Product p2("X2", "Toy X2", 8.3);

    Catalogue catalogue(Catalogue::inventory_t{
            {p1.get_id(), p1},
            {p2.get_id(), p2},
    });

    std::function<bool (double)> predicate = [](double price) {
        return (price < 10.0);
    };
    auto filtered_products = catalogue.get_products_with_appropriate_price(predicate);

    ASSERT_EQ(filtered_products.size(), 1U);
    EXPECT_EQ(filtered_products[0].get_id(), p2.get_id());
}

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// ...

using ::testing::Property;

// ...

TEST(CatalogueTest, get_products_by_name_part_case_sensitive) {
    Product p1("X1", "TOY uppercase", 10);
    Product p2("X2", "toy lowercase", 10);

    Catalogue catalogue(Catalogue::inventory_t{
            {p1.get_id(), p1},
            {p2.get_id(), p2},
    });

    auto filtered_products = catalogue.get_products_by_name_part("toy", true);

    ASSERT_EQ(filtered_products.size(), 1U);
    EXPECT_EQ(filtered_products[0].get_id(), p2.get_id());
}

TEST(CatalogueTest, get_products_by_name_part_case_insensitive) {
    Product p1("X1", "TOY uppercase", 10);
    Product p2("X2", "toy lowercase", 10);

    Catalogue catalogue(Catalogue::inventory_t{
            {p1.get_id(), p1},
            {p2.get_id(), p2},
    });

    auto filtered_products = catalogue.get_products_by_name_part("toy");

    ASSERT_EQ(filtered_products.size(), 2U);

    // Upewnij się, że wektor z wynikami zawiera element, którego metoda
    // `Product::get_id()` zwraca wartość `p1.get_id()`.
    EXPECT_THAT(filtered_products, Contains(Property(&Product::get_id, p1.get_id())));

    EXPECT_THAT(filtered_products, Contains(Property(&Product::get_id, p2.get_id())));
}