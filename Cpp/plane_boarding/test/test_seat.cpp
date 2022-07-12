//
// Created by kubak on 16.06.2022.
//
#include "seats_rows.hpp"
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
    std::unique_ptr<PassengerOnBoard> passenger_ptr = std::make_unique<PassengerOnBoard>(3, 5);
    seat.take_seat(std::move(passenger_ptr));
    EXPECT_EQ(seat.is_taken(), true);
    passenger_ptr = seat.free_seat();
    EXPECT_EQ(passenger_ptr->is_sitting(), false);
    EXPECT_EQ(seat.is_taken(), false);
}

TEST(RowTest, CreateRow) {
    Row row(5, 6);
    EXPECT_EQ(row.get_row_nr(), 5);
    EXPECT_EQ(row.get_seats_nr(), 6);
    EXPECT_EQ(row.seat()[0].get_row(), 5);
    EXPECT_EQ(row.seat()[5].get_position(), 5);
}

TEST(RowTest, EnterRowTest) {
    Row row(3,6);
    std::unique_ptr<PassengerOnBoard> passenger1 = std::make_unique<PassengerOnBoard>(3, 2);
    std::unique_ptr<PassengerOnBoard> passenger2 = std::make_unique<PassengerOnBoard>(3, 5);
    row.enter_row(std::move(passenger1));
    row.enter_row(std::move(passenger2));
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    EXPECT_NE(row.buffer()[2], nullptr);
    EXPECT_NE(row.buffer()[3], nullptr);
    EXPECT_EQ(row.buffer()[4], nullptr);
    EXPECT_EQ(row.buffer()[5], nullptr);

}

TEST(RowTest, moveInRowTest) {
    Row row(3,6);
    std::unique_ptr<PassengerOnBoard> passenger1 = std::make_unique<PassengerOnBoard>(3, 2);
    std::unique_ptr<PassengerOnBoard> passenger2 = std::make_unique<PassengerOnBoard>(3, 5);
    row.enter_row(std::move(passenger1));
    row.enter_row(std::move(passenger2));
    row.step_forward_row();
    row.step_forward_row();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    EXPECT_NE(row.buffer()[2], nullptr);
    EXPECT_EQ(row.buffer()[3], nullptr);
    EXPECT_EQ(row.buffer()[4], nullptr);
    EXPECT_NE(row.buffer()[5], nullptr);
}

TEST(RowTest, stepInRowDelayTest) {
    Row row(3,6);
    std::unique_ptr<PassengerOnBoard> passenger0 = std::make_unique<PassengerOnBoard>(3, 0);
    std::unique_ptr<PassengerOnBoard> passenger1 = std::make_unique<PassengerOnBoard>(3, 1);
    std::unique_ptr<PassengerOnBoard> passenger2 = std::make_unique<PassengerOnBoard>(3, 2);
    row.enter_row(std::move(passenger2));
    row.sit();
    ASSERT_EQ(row.seat()[2].is_taken(), true);\
    row.enter_row(std::move(passenger1));
    row.step_forward_row();
    EXPECT_EQ(row.buffer()[1], nullptr);
    row.step_forward_row();
    EXPECT_NE(row.buffer()[1], nullptr);
    row.sit();
    EXPECT_EQ(row.buffer()[1], nullptr);
    row.enter_row(std::move(passenger0));
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    row.step_forward_row();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    row.step_forward_row();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_NE(row.buffer()[1], nullptr);
    row.step_forward_row();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_NE(row.buffer()[1], nullptr);
    row.step_forward_row();
    EXPECT_NE(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    row.sit();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
}

TEST(RowTest, sitTest) {
    Row row(3,6);
    std::unique_ptr<PassengerOnBoard> passenger1 = std::make_unique<PassengerOnBoard>(3, 2);
    std::unique_ptr<PassengerOnBoard> passenger2 = std::make_unique<PassengerOnBoard>(3, 5);
    row.enter_row(std::move(passenger1));
    row.enter_row(std::move(passenger2));
    row.sit();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    EXPECT_EQ(row.buffer()[2], nullptr);
    EXPECT_NE(row.buffer()[3], nullptr);
    EXPECT_EQ(row.buffer()[4], nullptr);
    EXPECT_EQ(row.buffer()[5], nullptr);
    row.step_forward_row();
    row.step_forward_row();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    EXPECT_EQ(row.buffer()[2], nullptr);
    EXPECT_EQ(row.buffer()[3], nullptr);
    EXPECT_EQ(row.buffer()[4], nullptr);
    EXPECT_NE(row.buffer()[5], nullptr);
    row.sit();
    EXPECT_EQ(row.buffer()[0], nullptr);
    EXPECT_EQ(row.buffer()[1], nullptr);
    EXPECT_EQ(row.buffer()[2], nullptr);
    EXPECT_EQ(row.buffer()[3], nullptr);
    EXPECT_EQ(row.buffer()[4], nullptr);
    EXPECT_EQ(row.buffer()[5], nullptr);

}

