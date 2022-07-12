//
// Created by kubak on 12.07.2022.
//

#ifndef PLANE_BOARDING_REPORTS_HPP
#define PLANE_BOARDING_REPORTS_HPP

#include "board.hpp"

// Report helpers functions
size_t digit_nr(unsigned int nr);
size_t digit_max_index_nr(unsigned int nr);
size_t get_position_width(const Board& board);
std::string position_correct_width(unsigned int act_row, unsigned int rows_nr, unsigned int act_seat, unsigned int seats_nr);
std::string upper_line(const Board& board);
std::string line_passenger(const Board& board, unsigned int line_nr);
std::string queue_aisle_line(const Board& board);
#endif //PLANE_BOARDING_REPORTS_HPP
