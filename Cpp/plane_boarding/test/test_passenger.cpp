//
// Created by kubak on 16.06.2022.
//
#include "passenger.hpp"
#include "gtest/gtest.h"

TEST(TestPassenger, createPassenger) {
    Passenger passenger(0U, "John", "Smith", 40, "Main Street 6", "Ohio", "383338338", true);
    ASSERT_EQ(passenger.get_id(), 0);
    ASSERT_EQ(passenger.getName(), "John");
    ASSERT_EQ(passenger.getSurname(), "Smith");
    ASSERT_EQ(passenger.getAge(), 40);
    ASSERT_EQ(passenger.getAddress(), "Main Street 6");
    ASSERT_EQ(passenger.getCity(), "Ohio");
    ASSERT_EQ(passenger.getPhoneNr(), "383338338");
    ASSERT_EQ(passenger.handLuggageRegistered(), true);
}

TEST(TestPassengerOnBoard, createAnonymous) {
    PassengerOnBoard::reset_id();
    PassengerOnBoard passenger1(0,2,2,2);
    PassengerOnBoard passenger2(0,3,2,2);
    PassengerOnBoard passenger3(0,4,2,2);
    ASSERT_EQ(passenger1.get_id(), 1);
    ASSERT_EQ(passenger2.get_id(), 2);
    ASSERT_EQ(passenger3.get_id(), 3);
    ASSERT_EQ(passenger1.is_sitting(), false);
    ASSERT_EQ(passenger3.has_luggage(), true);
}

TEST(TestPassengerOnBoard, createPassengerOnBoard) {
    PassengerOnBoard::reset_id();
    PassengerOnBoard pas1(5, 1, 3, 1);
    ASSERT_EQ(pas1.get_id(), 1);

    EXPECT_EQ(pas1.get_seat_position(), 1);
    EXPECT_EQ(pas1.get_seat_row(), 5);
    EXPECT_EQ(pas1.loading_luggage_time(), 3);
    EXPECT_EQ(pas1.taking_luggage_time(), 1);
    EXPECT_EQ(pas1.is_sitting(), false);
    EXPECT_EQ(pas1.has_luggage(), true);
}

TEST(TestPassengerOnBoard, luggageTest) {
    PassengerOnBoard::reset_id();
    PassengerOnBoard passenger(3, 2, 3, 2);
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
