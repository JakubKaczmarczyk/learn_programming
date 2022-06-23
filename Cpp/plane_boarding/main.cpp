#include <iostream>
#include "board.hpp"
#include <iomanip>


extern int simulate_board(unsigned int rows_nr, unsigned int seats_in_row, QueueAlgorithm algorithm, LuggageTime luggageTimeType,
               unsigned int manage_luggage_time, unsigned int max_time, unsigned int min_time,
               const std::string &report_file_name, bool generate_report);

extern float simulation_loop(unsigned int iterations, unsigned int rows_nr, unsigned int seats_in_row, QueueAlgorithm algorithm,
                       unsigned int max_time, unsigned int min_time);


int main() {
    // Settings before simulation
    unsigned int rows_nr = 10U;
    unsigned int seats_in_row = 6U;
    LuggageTime luggageTimeType = LuggageTime::Fixed;
    unsigned int manage_luggage_time = 3U;
    unsigned int max_time = 5U;
    unsigned int min_time = 1U;
    // Loop
    bool do_iterations = true;
    unsigned int iterations = 500U;

    // Start Info
    std::cout << "Simulation settings: \nRows : " << rows_nr <<
                "\nSeats in row: " << seats_in_row <<
                "\nFixed time: " << manage_luggage_time <<
                "\nRandom time between " << min_time << " and " << max_time <<
                "\nDo iterations: " << do_iterations <<
                "\nIterations: " << iterations <<
                "\n\n" << std::endl;

    std::cout << "Back to front : " << simulate_board(rows_nr, seats_in_row,
                                                      QueueAlgorithm::BackToFront,
                                                      luggageTimeType,
                                                      manage_luggage_time,
                                                      max_time, min_time,
                                                      "raport_back_to_front.txt", true)
                                                      << std::endl;

    std::cout << "Front to back : " << simulate_board(rows_nr, seats_in_row,
                                                      QueueAlgorithm::FrontToBack,
                                                      luggageTimeType,
                                                      manage_luggage_time,
                                                      max_time, min_time,
                                                      "raport_front_to_back.txt", true)
                                                      << std::endl;

    std::cout << "Wiki : " << simulate_board(rows_nr, seats_in_row,
                                             QueueAlgorithm::Wiki,
                                             luggageTimeType,
                                             manage_luggage_time,
                                             max_time, min_time,
                                             "wiki.txt", true)
                                             << std::endl;


    std::cout << "Even windows : " << simulate_board(rows_nr, seats_in_row,
                                                     QueueAlgorithm::EvenWindows,
                                                     luggageTimeType,
                                                     manage_luggage_time,
                                                     max_time, min_time,
                                                     "raport_even_windows.txt", true)
                                                     << std::endl;

    if(!do_iterations) {
        return EXIT_SUCCESS;
    }

    std::cout << "Random average Back To Front : " << std::setprecision(2) << std::fixed <<
                               simulation_loop(iterations,
                               rows_nr, seats_in_row,
                               QueueAlgorithm::BackToFront,
                               max_time, min_time) << std::endl;

    std::cout << "Random average Front To Back : " << std::setprecision(2) << std::fixed <<
              simulation_loop(iterations,
                              rows_nr, seats_in_row,
                              QueueAlgorithm::FrontToBack,
                              max_time, min_time) << std::endl;

    std::cout << "Random average Wiki : " << std::setprecision(2) << std::fixed <<
              simulation_loop(iterations,
                              rows_nr, seats_in_row,
                              QueueAlgorithm::Wiki,
                              max_time, min_time) << std::endl;

    std::cout << "Random average Even Windows : " << std::setprecision(2) << std::fixed <<
              simulation_loop(iterations,
                              rows_nr, seats_in_row,
                              QueueAlgorithm::EvenWindows,
                              max_time, min_time) << std::endl;

    return EXIT_SUCCESS;
}
