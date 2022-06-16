//
// Created by kubak on 16.06.2022.
//
#include "seats.hpp"
#include "gtest/gtest.h"

TEST(SeatTest, createSeat) {
    Seat seat1(1);
    EXPECT_EQ(seat1.get_position(), 1);
    EXPECT_EQ(seat1.is_taken(), false);
    seat1.take_seat();
    EXPECT_EQ(seat1.is_taken(), true);
    seat1.free_seat();
    EXPECT_EQ(seat1.is_taken(), false);
}

TEST(RowTest, CreateRow) {
    Row row1(6);
    ASSERT_EQ(row1.size(), 6);
    int i = 1;
    for(auto const& it : row1) {
        EXPECT_EQ(it->get_position(), i);
        EXPECT_EQ(it->is_taken(), false);
        ++i;
    }
    row1[3]->take_seat();
    EXPECT_EQ(row1[3]->is_taken(), true);
}