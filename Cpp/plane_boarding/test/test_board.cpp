//
// Created by kubak on 17.06.2022.
//

#include "gtest/gtest.h"
#include "board.hpp"

TEST(BoardTest, createBoard) {
    Board board(10U, 6U);
    EXPECT_EQ(board.rows_nr(), 10U);
    EXPECT_EQ(board.seats_nr(), 6U);
}

TEST(BoardTest, outerQueueTest) {
    Board board(10U, 6U);
    board.set_luggage_time_settings( LuggageTime::Fixed, 1U, 0, 0);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    EXPECT_EQ(board.outer_queue().size(), 10U * 6U);

}

TEST(BoardTest, enqueueTest) {
    Board board(10U, 6U);
    board.set_luggage_time_settings( LuggageTime::Fixed, 1U, 0, 0);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    EXPECT_EQ(board.outer_queue().size(), 60U);
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.aisle()[0], nullptr);
    board.enqueue_passenger();
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.outer_queue()[0], nullptr);
    EXPECT_NE(board.aisle()[0], nullptr);
    EXPECT_EQ(board.aisle()[1], nullptr);
    board.enqueue_passenger();
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.outer_queue()[0], nullptr);
    EXPECT_NE(board.outer_queue()[1], nullptr);
    EXPECT_NE(board.aisle()[0], nullptr);
    EXPECT_EQ(board.aisle()[1], nullptr);

}

TEST(BoardTest, stepForwardTest) {
    Board board(10, 6);
    board.set_luggage_time_settings( LuggageTime::Fixed, 1U, 0, 0);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    EXPECT_EQ(board.outer_queue().size(), 60);
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.aisle()[0], nullptr);
    board.enqueue_passenger();
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.outer_queue()[0], nullptr);
    EXPECT_NE(board.aisle()[0], nullptr);
    EXPECT_EQ(board.aisle()[1], nullptr);
    board.enqueue_passenger();
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.outer_queue()[0], nullptr);
    EXPECT_NE(board.outer_queue()[1], nullptr);
    EXPECT_NE(board.aisle()[0], nullptr);
    EXPECT_EQ(board.aisle()[1], nullptr);
    board.step_forward();
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.outer_queue()[0], nullptr);
    EXPECT_NE(board.outer_queue()[1], nullptr);
    EXPECT_EQ(board.aisle()[0], nullptr);
    EXPECT_NE(board.aisle()[1], nullptr);
    board.enqueue_passenger();
    EXPECT_NE(board.outer_queue()[59], nullptr);
    EXPECT_EQ(board.outer_queue()[0], nullptr);
    EXPECT_EQ(board.outer_queue()[1], nullptr);
    EXPECT_NE(board.aisle()[0], nullptr);
    EXPECT_NE(board.aisle()[1], nullptr);
}
TEST(BoardTest, stepForwardTestFin) {
    Board board(10, 6);
    board.set_luggage_time_settings( LuggageTime::Fixed, 1U, 0, 0);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    for(int i = 0; i < 15; ++i) {
        board.step_forward();
    }
    EXPECT_EQ(board.aisle()[8], nullptr);
    EXPECT_NE(board.aisle()[9], nullptr);
}

TEST(BoardTest, loadLuggageTest) {
    Board board(10, 6);
    board.set_luggage_time_settings( LuggageTime::Fixed, 2U, 0, 0);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    for(int i = 0; i < 15; ++i) {
        board.step_forward();
    }
    board.load_luggage();
    EXPECT_EQ(board.aisle()[9]->has_luggage(), true);
    board.load_luggage();
    EXPECT_EQ(board.aisle()[9]->has_luggage(), false);

}

TEST(BoardTest, EnterRow) {
    Board board(10, 6);
    board.set_luggage_time_settings( LuggageTime::Fixed, 1U, 0, 0);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    board.enqueue_passenger();
    board.step_forward();
    board.enqueue_passenger();
    board.enter_rows();
    ASSERT_EQ(board.aisle()[0]->get_seat_row(), 9);
    ASSERT_EQ(board.aisle()[1]->get_seat_row(), 9);
    for(int i = 0; i < 15; ++i) {
        board.step_forward();
    }
    board.load_luggage();
    ASSERT_EQ(board.aisle()[9]->has_luggage(), false);
    board.enter_rows();
    EXPECT_EQ(board.aisle()[9], nullptr);
    board.step_forward();
    EXPECT_EQ(board.aisle()[9]->has_luggage(), true);
    board.load_luggage();
    EXPECT_EQ(board.aisle()[9]->has_luggage(), false);
}

TEST(BoardTest, fullTest) {
    Board board(2, 4);
    board.set_luggage_time_settings( LuggageTime::Fixed, 1U, 0, 0);
    board.create_outer_queue(QueueAlgorithm::BackToFront);
    int i = 0;
    while(!board.is_boarding_finished()) {
        board.step_forward();
        board.step_forward_row();
        board.enter_rows();
        board.sit();
        board.load_luggage();
        board.enqueue_passenger();
        ++i;
    }
    EXPECT_GT(i, 14);
}
