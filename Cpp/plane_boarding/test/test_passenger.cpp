//
// Created by kubak on 16.06.2022.
//
#include "passenger.hpp"
#include "gtest/gtest.h"

TEST(TestPassenger, createPassenger) {
    Passenger::reset_id();
    Passenger pas1(5, 1,3,1);
    ASSERT_EQ(pas1.get_id(), 1);

    EXPECT_EQ(pas1.seat_position(), 1);
    EXPECT_EQ(pas1.seat_row(), 5);
    EXPECT_EQ(pas1.loading_luggage_time(), 3);
    EXPECT_EQ(pas1.taking_luggage_time(), 1);
    EXPECT_EQ(pas1.is_sitting(), false);
    EXPECT_EQ(pas1.has_luggage(), true);
}

TEST(TestPassenger, luggageTest) {
    Passenger::reset_id();
    Passenger passenger(3,2,3,2);
    EXPECT_EQ(passenger.has_luggage(), true);
    EXPECT_EQ(passenger.is_sitting(), false);
    passenger.load_luggage();
    EXPECT_EQ(passenger.has_luggage(), true);
    passenger.load_luggage();
    EXPECT_EQ(passenger.has_luggage(), true);
    passenger.load_luggage();
    EXPECT_EQ(passenger.has_luggage(), false);
    passenger.sit();
    EXPECT_EQ(passenger.is_sitting(), true);
    passenger.stand_up();
    EXPECT_EQ(passenger.is_sitting(), false);
    passenger.take_luggage();
    EXPECT_EQ(passenger.has_luggage(), false);
    passenger.take_luggage();
    EXPECT_EQ(passenger.has_luggage(), true);
}
