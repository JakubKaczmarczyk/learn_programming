//
// Created by kubak on 16.06.2022.
//
#include "board.hpp"

int simulate_board(int row_nr, int seats_in_row, QueueAlgorithm algorithm, std::string raport_file_name) {
    Board board(row_nr, seats_in_row);
    board.clear_report(raport_file_name);
    board.create_outer_queue(algorithm);
    int i = 0;
    while(!board.is_boarding_finished()) {
        board.generate_tour_report(i, raport_file_name);
        board.enter_rows();
        board.sit();
        board.load_luggage();
        board.step_forward();
        board.enqueue_passenger();
        ++i;
    }
    board.generate_tour_report(i, raport_file_name);
    return i;
}