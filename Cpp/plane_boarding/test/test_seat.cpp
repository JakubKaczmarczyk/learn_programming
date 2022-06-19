//
// Created by kubak on 16.06.2022.
//
#include "seats.hpp"
#include "gtest/gtest.h"

TEST(SeatTest, createSeat) {
    Seat seat(3, 5);
    EXPECT_EQ(seat.get_position(), 5);
    EXPECT_EQ(seat.get_row(), 3);
    EXPECT_EQ(seat.is_taken(), false);


}

TEST(SeatTest, sittingTest) {
    Seat seat(3, 5);
    EXPECT_EQ(seat.is_taken(), false);
    std::unique_ptr<Passenger> passenger_ptr = std::make_unique<Passenger>(3,5);
    seat.take_seat(std::move(passenger_ptr));
    EXPECT_EQ(seat.is_taken(), true);
    passenger_ptr = seat.free_seat();
    EXPECT_EQ(passenger_ptr->is_sitting(), false);
    EXPECT_EQ(seat.is_taken(), false);
}

TEST(RowTest, CreateRow) {
    Row row(5, 6);
    EXPECT_EQ(row.row_nr(), 5);
    EXPECT_EQ(row.seats_nr(), 6);
    EXPECT_EQ(row[0].get_row(), 5);
    EXPECT_EQ(row[5].get_position(), 5);
}

//TEST(RowTest, EnterRowTest) {
//    Row row(3,6);
//    std::unique_ptr<Passenger> passenger1 = std::make_unique<Passenger>(3, 2);
//    std::unique_ptr<Passenger> passenger2 = std::make_unique<Passenger>(3, 5);
//    row.enter_row(std::move(passenger1));
//    row.enter_row(std::move(passenger2));
//    EXPECT_EQ(row.H_buffer_size(), 1);
//    EXPECT_EQ(row.L_buffer_size(), 1);
//}
//
//TEST(RowTest, sitTest) {
//    Row row(3,6);
//    std::unique_ptr<Passenger> passenger1 = std::make_unique<Passenger>(3, 2);
//    std::unique_ptr<Passenger> passenger2 = std::make_unique<Passenger>(3, 5);
//    row.enter_row(std::move(passenger1));
//    row.enter_row(std::move(passenger2));
//    row.sit();
//    EXPECT_EQ(row.H_buffer_size(), 0);
//    EXPECT_EQ(row.L_buffer_size(), 0);
//    EXPECT_EQ(row[0].is_taken(), false);
//    EXPECT_EQ(row[1].is_taken(), false);
//    EXPECT_EQ(row[2].is_taken(), true);
//    EXPECT_EQ(row[3].is_taken(), false);
//    EXPECT_EQ(row[4].is_taken(), false);
//    EXPECT_EQ(row[5].is_taken(), true);
//
//}
//
