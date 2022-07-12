//
// Created by kubak on 12.07.2022.
//
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include "reports.hpp"

void Board::clear_report(const std::string& report_file_name) {
    std::fstream f1(report_file_name, std::ios::out);
    if(f1.is_open()) {
        f1 << "";
    }
    f1.close();
}

void Board::generate_tour_report(unsigned int turn, const std::string& report_file_name) const {
    std::fstream f(report_file_name, std::ios::app);
    if(f.is_open()) {
        f << upper_line(*this);
        f << "\nTurn " << turn << " Queue:\n";
        // seats upper
        for (unsigned int seat_it = 0; seat_it < seats_nr_ / 2; ++seat_it) {
            f << line_passenger(*this, seat_it);
        }
        // Queue and aisle_
        f << queue_aisle_line(*this);
        // seats lower
        for (unsigned int seat_it = seats_nr_ / 2; seat_it < seats_nr_; ++seat_it) {
            f << line_passenger(*this, seat_it);
        }
    }
    f.close();
}

size_t digit_nr(unsigned int nr) {
    return (nr == 0) ? 1 : static_cast<unsigned int>(log10(static_cast<double>(nr)) + 1);
}

size_t digit_max_index_nr(unsigned int nr) {
    return (nr==0 || nr==1) ? 1 : digit_nr(nr-1);
}

size_t get_position_width(const Board& board) {
    unsigned int seats_nr = board.get_seats_nr();
    unsigned int rows_nr = board.get_rows_nr();
    auto seats_w = digit_max_index_nr(seats_nr);
    auto rows_w = digit_max_index_nr(rows_nr);
    return static_cast<unsigned int>(seats_w + rows_w);
}

std::string position_correct_width(unsigned int act_row, unsigned int rows_nr, unsigned int act_seat, unsigned int seats_nr) {
    std::ostringstream actual_pos;
    size_t actual_row_digit_nr = digit_nr(act_row);
    for(size_t i = actual_row_digit_nr; i < digit_max_index_nr(rows_nr); ++i) {
        actual_pos << ' ';
    }
    actual_pos << act_row;
    size_t actual_seat_digit_nr = digit_nr(act_seat);
    for(size_t i = actual_seat_digit_nr; i < digit_max_index_nr(seats_nr); ++i) {
        actual_pos << '0';
    }
    actual_pos << act_seat;
    return actual_pos.str();

}

std::string upper_line(const Board& board) {
    unsigned int seats_nr = board.get_seats_nr();
    unsigned int rows_nr = board.get_rows_nr();
    std::ostringstream oss;
    size_t position_width = get_position_width(board);
    std::string empty_position = std::string(position_width, 'X');
    for(unsigned int i = 0; i < seats_nr*rows_nr; ++i) {
        oss << empty_position << 'X';
    }
    oss << 'X';
    for(unsigned int i = 0; i < rows_nr; ++i) {
        oss << empty_position << 'X' << empty_position << 'X';
    }

    return oss.str();
}

std::string line_passenger(const Board& board, unsigned int line_nr) {
    unsigned int seats_nr = board.get_seats_nr();
    unsigned int rows_nr = board.get_rows_nr();
    std::ostringstream oss;
    size_t position_width = get_position_width(board);

    char empty_char_filler;
    if (line_nr < seats_nr/2-1 || line_nr > seats_nr/2) {
        empty_char_filler = ' ';
    } else {
        empty_char_filler = '-';
    }
    std::string empty_queue_string(position_width, empty_char_filler);
    for(unsigned int i = 0; i < seats_nr*rows_nr; ++i) {
        oss << empty_queue_string << empty_char_filler;
    }
    oss << '|';
    std::string empty_position(position_width, ' ');

    for(const auto& row_it : board.rows()) {
        std::ostringstream actual_pos;
        if (row_it.buffer()[line_nr] != nullptr) {
            const std::unique_ptr<PassengerOnBoard>* passenger_ptr = &row_it.buffer()[line_nr];
            actual_pos << position_correct_width((*passenger_ptr)->get_seat_row(), rows_nr,
                                                 (*passenger_ptr)->get_seat_position(), seats_nr);
        } else {
            actual_pos << empty_position;
        }
        actual_pos << ' ';
        if(row_it.seat()[line_nr].is_taken()) {
            actual_pos << position_correct_width(row_it.get_row_nr(), rows_nr, line_nr, seats_nr);
        } else {
            actual_pos << std::string(position_width, ' ');
        }
        oss << actual_pos.str() << '|';
    }
    oss << '\n';
    return oss.str();
}

std::string queue_aisle_line(const Board& board) {
    unsigned int seats_nr = board.get_seats_nr();
    unsigned int rows_nr = board.get_rows_nr();
    std::ostringstream oss;
    size_t position_width = get_position_width(board);
    std::string empty_position(position_width, ' ');
    for (auto &passenger: board.outer_queue()) {
        if (passenger == nullptr) {
            oss << empty_position;
        } else {
            oss << position_correct_width(passenger->get_seat_row(), rows_nr, passenger->get_seat_position(), seats_nr);
        }
        oss << ' ';
    }
    oss << ' ';
    for (auto &passenger: board.aisle()) {

        if (passenger == nullptr) {
            oss << empty_position;
        } else {
            oss << position_correct_width(passenger->get_seat_row(), rows_nr, passenger->get_seat_position(), seats_nr);
        }
        oss << ' ';
        oss << empty_position << ' ';
    }
    oss << '\n';
    return oss.str();
}