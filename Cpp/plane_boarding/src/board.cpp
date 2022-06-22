//
// Created by kubak on 16.06.2022.
//

#include "board.hpp"
#include <sstream>
#include <fstream>
#include <cmath>
#include <limits>


Board::Board(unsigned int rows_nr, unsigned int seats_in_row) {
    rows_nr_ = rows_nr;
    seats_nr_ = seats_in_row;
    for(unsigned int i = 0; i < rows_nr; ++i) {
        rows_.push_back(Row(i, seats_nr_));
        aisle_.push_back(nullptr);
    }
    for(unsigned int i = 0; i < rows_nr_*seats_nr_; ++i) {
        outer_queue_.push_back(nullptr);
    }
}


void
Board::create_outer_queue(QueueAlgorithm algorithm, LuggageTime luggage_time_type, unsigned int load_luggage_time,
                          unsigned int take_luggage_time) {
    if (luggage_time_type == LuggageTime::Random) {
        load_luggage_time = static_cast<unsigned int>(rand() % (4 - 1 + 1) + 1);
    }
    size_t queue_it = static_cast<size_t>(rows_nr_*seats_nr_-1);
    switch (algorithm) {
        case QueueAlgorithm::BackToFront: {
            for (unsigned int row_it = rows_nr_ - 1; row_it != std::numeric_limits<unsigned int>::max(); --row_it) {
                for (unsigned int seat_it = 0; seat_it < seats_nr_; ++seat_it) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, seat_it, load_luggage_time, take_luggage_time);
                    --queue_it;
                }
            }
            break;
        }
        case QueueAlgorithm::FrontToBack: {
            for (unsigned int row_it = 0; row_it < rows_nr_; ++row_it) {
                for (unsigned int seat_it = 0; seat_it < seats_nr_; ++seat_it) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, seat_it, load_luggage_time, take_luggage_time);
                    --queue_it;
                }
            }
            break;
        }
        case QueueAlgorithm::Wiki: {
            std::vector<unsigned int> seats_numbers;
            unsigned int down_it = 0U;
            unsigned int up_it = seats_nr_-1;
            while (down_it<up_it) {
                seats_numbers.push_back(down_it);
                seats_numbers.push_back(up_it);
                ++down_it;
                --up_it;
            }
            for (auto const &seat_it: seats_numbers) {
                for (unsigned int row_it = rows_nr_ - 1; row_it != std::numeric_limits<unsigned int>::max(); --row_it) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, seat_it, load_luggage_time, take_luggage_time);
                    --queue_it;
                }
            }
            break;
        }
        case QueueAlgorithm::EvenWindows: {
            std::vector<std::pair<unsigned int, unsigned int>> seats_pairs;
            unsigned int down_it = 0U;
            unsigned int up_it = seats_nr_-1;
            while (down_it<up_it) {
                seats_pairs.push_back(std::make_pair(down_it, up_it));
                ++down_it;
                --up_it;
            }
            for(auto& pair_it : seats_pairs) {
                unsigned int lower_sit = pair_it.first;
                unsigned int upper_sit = pair_it.second;
                for(unsigned int row_it = rows_nr_ - 1;
                    (row_it != std::numeric_limits<unsigned int>::max() &&
                    row_it != std::numeric_limits<unsigned int>::max() -1);
                    row_it = row_it - 2) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, lower_sit,load_luggage_time,take_luggage_time);
                    --queue_it;
                }
                for(unsigned int row_it = rows_nr_ - 1;
                    (row_it != std::numeric_limits<unsigned int>::max() &&
                     row_it != std::numeric_limits<unsigned int>::max() -1);
                    row_it = row_it - 2) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, upper_sit,load_luggage_time,take_luggage_time);
                    --queue_it;
                }
                for (unsigned int row_it = rows_nr_ - 2;
                     (row_it != std::numeric_limits<unsigned int>::max() &&
                      row_it != std::numeric_limits<unsigned int>::max() - 1);
                     row_it = row_it - 2) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, lower_sit, 1U, 1U);
                    --queue_it;
                }
                for (unsigned int row_it = rows_nr_ - 2;
                     (row_it != std::numeric_limits<unsigned int>::max() &&
                      row_it != std::numeric_limits<unsigned int>::max() - 1);
                     row_it = row_it - 2) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, upper_sit, 1U, 1U);
                    --queue_it;
                }
            }
            break;
        }
        default: {
            break;
        }
    }
}


std::string Board::outer_queue_string() const {
    std::ostringstream oss;
    for(const auto& passenger : outer_queue_) {
        oss << "(" << passenger->seat_row() << " " << passenger->seat_position() << ")\n";
    }
    return oss.str();

}

void Board::enqueue_passenger() {
    if (aisle_[0] != nullptr) {
        return;
    }
    if (outer_queue_[static_cast<size_t>(rows_nr_*seats_nr_-1)] == nullptr) {
        return;
    }
    aisle_[0] = std::move(outer_queue_[static_cast<size_t>(rows_nr_*seats_nr_-1)]);
    outer_queue_.pop_back();
    outer_queue_.insert(outer_queue_.begin(), nullptr);
}

void Board::step_forward() {
    for(size_t i = static_cast<size_t>(rows_nr_-1); i >= 1; --i) {
        if (aisle_[i-1] != nullptr && aisle_[i] == nullptr && aisle_[i-1]->seat_row() != static_cast<unsigned int>(i-1)) {
            aisle_[i] = std::move(aisle_[i-1]);
            aisle_[i-1] = nullptr;
        }
    }
}



void Board::load_luggage() {
    for(size_t i = 0; i < aisle_.size(); ++i) {
        if (aisle_[i] == nullptr) {
            continue;
        }
        if (aisle_[i]->seat_row() != static_cast<unsigned int>(i) ) {
            continue;
        }
        aisle_[i] -> load_luggage();
    }
}

void Board::enter_rows() {
    std::vector<bool> may_enter_row(static_cast<size_t>(rows_nr_), false);
    for(size_t i = 0; i < static_cast<size_t>(rows_nr_); ++i) {
        if (aisle_[i] != nullptr) {
            may_enter_row[i] = rows_[i].may_passenger_enter_row(
                    aisle_[i]->seat_row(), aisle_[i]->seat_position());
        }
    }
    for(size_t i = 0; i < static_cast<size_t>(rows_nr_); ++i) {
        if (aisle_[i] == nullptr) {
            continue;
        }
        if (aisle_[i]->has_luggage()) {
            continue;
        }
        if (!may_enter_row[i]) {
            continue;
        }
        rows_[i].enter_row(std::move(aisle_[i]));
        aisle_[i] = nullptr;

    }
}

void Board::step_forward_row() {
    for(auto& row : rows_) {
        row.step_forward_row();
    }

}
void Board::sit() {
    for(auto& row : rows_) {
        row.sit();
    }
}

bool Board::is_boarding_finished() const {
    for(auto& row : rows_) {
        for(size_t i = 0; i < static_cast<size_t>(seats_nr_); ++i) {
            if( !row.seat()[i].is_taken() ) {
                return false;
            }
        }
    }
    return true;
}

void Board::clear_report(std::string name) const {
    std::fstream f1(name, std::ios::out);
    if(f1.is_open()) {
        f1 << "";
    }
    f1.close();
}

size_t digit_nr(unsigned int nr) {
    return (nr == 0) ? 1 : static_cast<unsigned int>(log10(static_cast<double>(nr)) + 1);
}

size_t digit_max_index_nr(unsigned int nr) {
    return (nr==0 || nr==1) ? 1 : digit_nr(nr-1);
}

size_t get_position_width(const Board& board) {
    unsigned int seats_nr = board.seats_nr();
    unsigned int rows_nr = board.rows_nr();
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
    unsigned int seats_nr = board.seats_nr();
    unsigned int rows_nr = board.rows_nr();
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
    unsigned int seats_nr = board.seats_nr();
    unsigned int rows_nr = board.rows_nr();
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
            const std::unique_ptr<Passenger>* passenger_ptr = &row_it.buffer()[line_nr];
            actual_pos << position_correct_width((*passenger_ptr)->seat_row(), rows_nr, (*passenger_ptr)->seat_position(), seats_nr);
        } else {
            actual_pos << empty_position;
        }
        actual_pos << ' ';
        if(row_it.seat()[line_nr].is_taken()) {
            actual_pos << position_correct_width(row_it.row_nr(), rows_nr, line_nr, seats_nr);
        } else {
            actual_pos << std::string(position_width, ' ');
        }
        oss << actual_pos.str() << '|';
    }
    oss << '\n';
    return oss.str();
}

std::string queue_aisle_line(const Board& board) {
    unsigned int seats_nr = board.seats_nr();
    unsigned int rows_nr = board.rows_nr();
    std::ostringstream oss;
    size_t position_width = get_position_width(board);
    std::string empty_position(position_width, ' ');
    for(auto& passenger : board.outer_queue()) {
        if(passenger == nullptr) {
            oss << empty_position;
        } else {
            oss << position_correct_width(passenger->seat_row(), rows_nr, passenger->seat_position(), seats_nr);
        }
        oss << ' ';
    }
    oss << ' ';
    for(auto& passenger : board.aisle()) {

        if(passenger == nullptr) {
            oss << empty_position;
        } else {
            oss << position_correct_width(passenger->seat_row(), rows_nr, passenger->seat_position(), seats_nr);
        }
        oss << ' ';
        oss << empty_position << ' ';
    }
    oss << '\n';
    return oss.str();
}
void Board::generate_tour_report(int turn, std::string name) const {
    std::fstream f(name, std::ios::app);
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