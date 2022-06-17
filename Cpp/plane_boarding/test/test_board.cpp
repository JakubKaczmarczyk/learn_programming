//
// Created by kubak on 17.06.2022.
//

#include "gtest/gtest.h"
#include "board.hpp"

TEST(BoardTest, createBoard) {
    Board board(10, 6);
    EXPECT_EQ(board.get_rows_nr(), 10);
    EXPECT_EQ(board.get_seats_nr(), 6);
}

TEST(BoardTest, outerQueueTest) {
    Board board(10, 6);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    EXPECT_EQ(board.outer_queue_size(), 10 * 6);

}

TEST(BoardTest, enqueueTest) {
    Board board(10, 6);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    EXPECT_EQ(board.outer_queue_size(), 60);
    EXPECT_EQ(board.passenger_queued(), 0);
    board.enqueue_passenger();
    EXPECT_EQ(board.outer_queue_size(), 59);
    EXPECT_EQ(board.passenger_queued(), 1);
    board.enqueue_passenger();
    EXPECT_EQ(board.outer_queue_size(), 59);
    EXPECT_EQ(board.passenger_queued(), 1);

}
TEST(BoardTest, stepForwardTest) {
    Board board(10, 6);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    board.step_forward();
    board.enqueue_passenger();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    board.step_forward();
    EXPECT_EQ(board.outer_queue_size(), 58);
    EXPECT_EQ(board.passenger_queued(), 2);
    EXPECT_EQ(board.passenger_seat_row_in_aisle(9), 9);
    EXPECT_EQ(board.passenger_seat_row_in_aisle(8), 9);


}

TEST(BoardTest, loadLuggageTest) {
    Board board(10, 6);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    for(int i = 0; i < 15; ++i) {
        board.step_forward();
    }
    board.load_luggage();
    EXPECT_EQ(board.passenger_in_aisle_has_luggage(9), false);

}

TEST(BoardTest, EnterRow) {
    Board board(10, 6);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    board.step_forward();
    board.enqueue_passenger();
    board.enter_rows();
    ASSERT_EQ(board.passenger_seat_row_in_aisle(0),9);
    ASSERT_EQ(board.passenger_seat_row_in_aisle(1),9);
    for(int i = 0; i < 15; ++i) {
        board.step_forward();
    }
    board.load_luggage();
    ASSERT_EQ(board.passenger_in_aisle_has_luggage(9), false);
    board.enter_rows();
    EXPECT_EQ(board.passenger_in_aisle_has_luggage(9), NULL);
    board.step_forward();
    EXPECT_EQ(board.passenger_in_aisle_has_luggage(9), true);
    board.load_luggage();
    EXPECT_EQ(board.passenger_in_aisle_has_luggage(9), false);


}