//
// Created by kubak on 16.06.2022.
//
#include "board.hpp"

int simulate_board(unsigned int row_nr, unsigned int seats_in_row, QueueAlgorithm algorithm, LuggageTime luggageTime, std::string raport_file_name, unsigned int load_time=2U, unsigned int take_time=2U) {
    Board board(row_nr, seats_in_row);
    board.clear_report(raport_file_name);
    board.create_outer_queue(algorithm, luggageTime, load_time, take_time);
    int i = 0;
    while(!board.is_boarding_finished()) {
        board.generate_tour_report(i, raport_file_name);
        board.sit();
        board.step_forward_row();
        board.enter_rows();
        board.load_luggage();
        board.step_forward();
        board.enqueue_passenger();
        ++i;
    }
    board.generate_tour_report(i, raport_file_name);
    return i;
}