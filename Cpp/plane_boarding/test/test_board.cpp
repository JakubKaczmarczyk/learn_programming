//
// Created by kubak on 17.06.2022.
//

#include "gtest/gtest.h"
#include "board.hpp"

TEST(BoardTest, createBoard) {
    Board board(10, 6);
    EXPECT_EQ(board.rows_nr(), 10);
    EXPECT_EQ(board.seats_nr(), 6);
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
    for(int i = 0; i < 10; ++i) {
        board.step_forward();
    }
    EXPECT_EQ(board.outer_queue_size(), 58);
    EXPECT_EQ(board.passenger_queued(), 2);
    EXPECT_EQ((*board[9])->seat_row(), 9);
    EXPECT_EQ((*board[8])->seat_row(), 9);


}

TEST(BoardTest, loadLuggageTest) {
    Board board(10, 6);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    for(int i = 0; i < 15; ++i) {
        board.step_forward();
    }
    board.load_luggage();
    EXPECT_EQ((*board[9])->has_luggage(), false);

}

TEST(BoardTest, EnterRow) {
    Board board(10, 6);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    board.step_forward();
    board.enqueue_passenger();
    board.enter_rows();
    ASSERT_EQ((*board[0])->seat_row(),9);
    ASSERT_EQ((*board[1])->seat_row(),9);
    for(int i = 0; i < 15; ++i) {
        board.step_forward();
    }
    board.load_luggage();
    ASSERT_EQ((*board[9])->has_luggage(), false);
    board.enter_rows();
    EXPECT_EQ((*board[9]), nullptr);
    board.step_forward();
    EXPECT_EQ((*board[9])->has_luggage(), true);
    board.load_luggage();
    EXPECT_EQ((*board[9])->has_luggage(), false);
}

TEST(BoardTest, fullTest) {
    Board board(2, 4);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    int i = 0;
    while(!board.is_boarding_finished()) {
        board.step_forward();
        board.enter_rows();
        board.sit();
        board.load_luggage();
        board.enqueue_passenger();
        ++i;
    }
    EXPECT_EQ(i, 16);
}

TEST(BoardTest, algorithmTest) {
    Board board1(2, 4);
    board1.create_outer_queue(QueueAlgorithm::BackToFront);
    int i = 0;
    while(!board1.is_boarding_finished()) {
        board1.enter_rows();
        board1.sit();
        board1.load_luggage();
        board1.step_forward();
        board1.enqueue_passenger();
        ++i;
    }
    Board board2(2, 4);
    board2.create_outer_queue(QueueAlgorithm::FrontToBack);
    int j = 0;
    while(!board2.is_boarding_finished()) {
        board2.enter_rows();
        board2.sit();
        board2.load_luggage();
        board2.step_forward();
        board2.enqueue_passenger();
        ++j;
    }
    EXPECT_GT(j, i);
}