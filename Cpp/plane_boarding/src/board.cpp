//
// Created by kubak on 16.06.2022.
//

#include "board.hpp"
#include <sstream>
#include <fstream>


Board::Board(int row_number, int seats_in_row) {
    rows_nr_ = row_number;
    seats_nr_ = seats_in_row;
    for(int i = 0; i < row_number; ++i) {
        rows_.push_back(Row(i, seats_nr_));
        aisle_.push_back(nullptr);
    }
}


void Board::create_outer_queue(QueueAlgorithm algorithm) {
    switch (algorithm) {
        case QueueAlgorithm::BackToFront:
            for(int row_it = rows_nr_-1; row_it >= 0; --row_it) {
                for(int seat_it = 0; seat_it < seats_nr_; ++seat_it) {
                    outer_queue_.push_back(std::make_unique<Passenger>(row_it, seat_it, 1, 2));
                }
            }
            break;
        case QueueAlgorithm::FrontToBack:
            for(int row_it = 0; row_it < rows_nr_; ++row_it) {
                for(int seat_it = 0; seat_it < seats_nr_; ++seat_it) {
                    outer_queue_.push_back(std::make_unique<Passenger>(row_it, seat_it, 1, 2));
                }
            }
            break;
        default:
            break;
    }
}

int Board::passenger_queued() const {
    int counter = 0;
    for(const auto& queue_pleace : aisle_) {
        if (queue_pleace != nullptr) {
            ++counter;
        }
    }
    return counter;
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
    if (outer_queue_.empty()) {
        return;
    }
    aisle_[0] = std::move(outer_queue_.front());
    outer_queue_.pop_front();
}

void Board::step_forward() {
    for(int i = rows_nr_-1; i >= 1; --i) {
        if (aisle_[i-1] != nullptr && aisle_[i] == nullptr && aisle_[i - 1]->seat_row() != i - 1) {
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
        if (aisle_[i]->seat_row() != static_cast<int>(i) ) {
            continue;
        }
        aisle_[i] -> load_luggage();
    }
}

void Board::enter_rows() {
    size_t i = -1;
    for(auto& row : rows_) {
        ++i;
        if (aisle_[i] == nullptr) {
            continue;
        }
        if (aisle_[i]->seat_row() != static_cast<int>(i) ) {
            continue;
        }
        if (aisle_[i]->has_luggage()) {
            continue;
        }
        row.enter_row(std::move(aisle_[i]));
        aisle_[i] = nullptr;

    }
    i = 0;
}

void Board::sit() {
    for(auto& row : rows_) {
        row.sit();
    }
}

bool Board::is_boarding_finished() const {
    for(auto& row : rows_) {
        for(size_t i = 0; i < static_cast<size_t>(seats_nr_); ++i) {
            if( !row[i].is_taken() ) {
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
void Board::generate_tour_report(int tour, std::string name) const {
    std::fstream f(name, std::ios::app);
    if(f.is_open()) {

        // upper line
        {
            // Queue
            for (int i = 0; i < seats_nr_ * rows_nr_; ++i) {
                f << "XXX";
            }
            // crossing
            f << "X";
            // board
            for (int i = 0; i < rows_nr_; ++i) {
                f << "XXX";
            }
            f << "\n";
        }
        f << "\nTour " << tour <<" Queue:\n";
        // seats upper
        {
            for(size_t seat_it = 0; seat_it < static_cast<size_t>(seats_nr_/2); ++seat_it) {
                // Queue
                std::string empty_space;
                if (seat_it < static_cast<size_t>(seats_nr_/2 - 1)) {
                    empty_space = "   ";
                } else {
                    empty_space = "---";
                }
                for (int i = 0; i < seats_nr_ * rows_nr_; ++i) {
                    f << empty_space;
                }
                // crossing
                f << "|";
                // board
                for (auto &row_it: rows_) {
                    if (row_it[seat_it].is_taken()) {
                        f << row_it[seat_it].get_row() << row_it[seat_it].get_position() << "|";
                    } else {
                        f << "  |";
                    }
                }
                f << "\n";
            }
        }

        // Queue and aisle_
        {
            // Queue
            {
                for (int j = 0; j < seats_nr_ * rows_nr_ - static_cast<int>(outer_queue_.size()); ++j) {
                    f << "   ";
                }
                for (auto passenger_ptr = outer_queue_.rbegin();
                     passenger_ptr != outer_queue_.rend(); ++passenger_ptr) {
                    f << (*passenger_ptr)->seat_row() << (*passenger_ptr)->seat_position() << " ";
                }
            }
            // crossing
            f << " ";
            // aisle_
            for(auto& it : aisle_) {
                if (it == nullptr) {
                    f << "   ";
                } else {
                    f << it->seat_row() << it->seat_position() << " ";
                }
            }
            f << "\n";
        }

        // seats lower
        {
            for(size_t seat_it = static_cast<size_t>(seats_nr_/2); seat_it < static_cast<size_t >(seats_nr_); ++seat_it) {
                // Queue
                std::string empty_space;
                if (seat_it == static_cast<size_t>(seats_nr_/2)) {
                    empty_space = "---";
                } else {
                    empty_space = "   ";
                }
                for (int i = 0; i < seats_nr_ * rows_nr_; ++i) {
                    f << empty_space;
                }
                // crossing
                f << "|";
                // board
                for (auto &row_it: rows_) {
                    if (row_it[seat_it].is_taken()) {
                        f << row_it[seat_it].get_row() << row_it[seat_it].get_position() << "|";
                    } else {
                        f << "  |";
                    }
                }
                f << "\n";
            }
        }
        f << "\n";
        }

    f.close();
}