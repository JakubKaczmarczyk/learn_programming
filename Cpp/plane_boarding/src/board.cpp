//
// Created by kubak on 16.06.2022.
//

#include "board.hpp"
#include <sstream>


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
                    outer_queue_.push_back(std::make_unique<Passenger>(row_it, seat_it));
                }
            }
            break;
        default:
            break;
    }
}
std::optional<int> Board::passenger_seat_row_in_aisle(size_t position) const {
    if (aisle_[position] == nullptr) {
        return NULL;
    }
    return aisle_[position]->get_seat_row();
}

std::optional<bool> Board::passenger_in_aisle_has_luggage(size_t position) const {
    if (aisle_[position] == nullptr) {
        return NULL;
    }
    return aisle_[position]->has_luggage();
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
        oss << "(" << passenger->get_seat_row() << " " << passenger->get_seat_position() << ")\n";
    }
    return oss.str();

}

void Board::enqueue_passenger() {
    if (aisle_[0] != nullptr) {
        return;
    }
    aisle_[0] = std::move(outer_queue_.front());
    outer_queue_.pop_front();
}

void Board::step_forward() {
    for(int i = rows_nr_-1; i >= 1; --i) {
        if (aisle_[i-1] != nullptr && aisle_[i] == nullptr && aisle_[i-1]->get_seat_row() != i-1) {
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
        if (aisle_[i]->get_seat_row() != static_cast<int>(i) ) {
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
        if (aisle_[i]->get_seat_row() != static_cast<int>(i) ) {
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