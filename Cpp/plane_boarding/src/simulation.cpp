//
// Created by kubak on 16.06.2022.
//
#include "board.hpp"
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>

unsigned int simulate_board(unsigned int rows_nr, unsigned int seats_in_row, QueueAlgorithm algorithm, LuggageTime luggageTimeType,
               unsigned int manage_luggage_time, unsigned int max_time, unsigned int min_time,
               const std::string &report_file_name, bool generate_report) {

    Board board(rows_nr, seats_in_row);
    if(generate_report) {
        board.clear_report(report_file_name);
    }
    board.create_outer_queue(algorithm, luggageTimeType, manage_luggage_time, max_time, min_time);
    unsigned int turn = 0;
    while(!board.is_boarding_finished()) {
        if(generate_report) {
            board.generate_tour_report(turn, report_file_name);
        }
        board.sit();
        board.step_forward_row();
        board.enter_rows();
        board.load_luggage();
        board.step_forward();
        board.enqueue_passenger();
        ++turn;
    }
    if(generate_report) {
        board.generate_tour_report(turn, report_file_name);
    }
    return turn;
}

float simulation_loop(unsigned int iterations, unsigned int rows_nr, unsigned int seats_in_row, QueueAlgorithm algorithm,
                      unsigned int max_time, unsigned int min_time) {
    std::vector<unsigned int>results;
    for(unsigned int i = 0; i < iterations; ++i) {
        results.push_back(simulate_board(rows_nr, seats_in_row,
                                         algorithm,
                                         LuggageTime::Random,
                                         0U,
                                         max_time, min_time,
                                         "", false));

    }

    auto const count = static_cast<double >(results.size());
    return static_cast<float>(std::accumulate(results.begin(), results.end(), 0)/count);
}