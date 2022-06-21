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


void Board::create_outer_queue(QueueAlgorithm algorithm) {
    size_t queue_it = static_cast<size_t>(rows_nr_*seats_nr_-1);
    switch (algorithm) {
        case QueueAlgorithm::BackToFront:
            for(unsigned int row_it = rows_nr_-1; row_it != std::numeric_limits<unsigned int>::max(); --row_it) {
                for(unsigned int seat_it = 0; seat_it < seats_nr_; ++seat_it) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, seat_it, 1, 2);
                    --queue_it;
                }
            }
            break;
        case QueueAlgorithm::FrontToBack:
            for(unsigned int row_it = 0; row_it < rows_nr_; ++row_it) {
                for(unsigned int seat_it = 0; seat_it < seats_nr_; ++seat_it) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, seat_it, 1, 2);
                    --queue_it;
                }
            }
            break;
        case QueueAlgorithm::Wiki:
            std::vector<unsigned int> seats_numbers = {0,5,1,4,2,3};
            for(auto const& seat_it : seats_numbers) {
                for (unsigned int row_it = rows_nr_ - 1; row_it != std::numeric_limits<unsigned int>::max(); --row_it) {
                    outer_queue_[queue_it] = std::make_unique<Passenger>(row_it, seat_it, 1, 2);
                    --queue_it;
                }
            }
            break;
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

//std::string upper_line_(unsigned int seats_nr, unsigned int rows_nr) {
//    std::ostringstream oss;
//    auto position_width = static_cast<unsigned int>(log10(static_cast<double>(seats_nr)) +
//            log10(static_cast<double>(rows_nr)) + 2);
//    return 0;
//}
void Board::generate_tour_report(int tour, std::string name) const {
    std::fstream f(name, std::ios::app);
    if(f.is_open()) {

        // upper line
        {
            // Queue
            for (unsigned int i = 0; i < seats_nr_ * rows_nr_; ++i) {
                f << "XXX";
            }
            // crossing
            f << "X";
            // board
            for (unsigned int i = 0; i < rows_nr_; ++i) {
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
                for (unsigned int i = 0; i < seats_nr_ * rows_nr_; ++i) {
                    f << empty_space;
                }
                // crossing
                f << "|";
                // board
                for (auto &row_it: rows_) {
                    if (row_it.seat()[seat_it].is_taken()) {
                        f << row_it.seat()[seat_it].get_row() << row_it.seat()[seat_it].get_position() << "|";
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
                for (auto& passenger : outer_queue_) {
                    if (passenger != nullptr) {
                        f << passenger->seat_row() << passenger->seat_position() << " ";
                    } else {
                        f << "   ";
                    }
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
                for (unsigned int i = 0; i < seats_nr_ * rows_nr_; ++i) {
                    f << empty_space;
                }
                // crossing
                f << "|";
                // board
                for (auto &row_it: rows_) {
                    if (row_it.seat()[seat_it].is_taken()) {
                        f << row_it.seat()[seat_it].get_row() << row_it.seat()[seat_it].get_position() << "|";
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