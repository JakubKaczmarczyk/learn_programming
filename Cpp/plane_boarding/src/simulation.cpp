//
// Created by kubak on 16.06.2022.
//
#include "board.hpp"

int simulate_board(unsigned int rows_nr, unsigned int seats_in_row, QueueAlgorithm algorithm, LuggageTime luggageTimeType,
                   unsigned int manage_luggage_time,
                   unsigned int max_time, unsigned int min_time,
                   const std::string& report_file_name) {

    Board board(rows_nr, seats_in_row);
    board.clear_report(report_file_name);
    board.create_outer_queue(algorithm, luggageTimeType, manage_luggage_time, max_time, min_time);
    int turn = 0;
    while(!board.is_boarding_finished()) {
        board.generate_tour_report(turn, report_file_name);
        board.sit();
        board.step_forward_row();
        board.enter_rows();
        board.load_luggage();
        board.step_forward();
        board.enqueue_passenger();
        ++turn;
    }
    board.generate_tour_report(turn, report_file_name);
    return turn;
}