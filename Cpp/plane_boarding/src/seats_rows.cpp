//
// Created by kubak on 16.06.2022.
//

#include "../include/seats_rows.hpp"

Seat::Seat(Seat &seat) {
    row_ = seat.row_;
    position_ = seat.position_;
    passenger_ = std::move(seat.passenger_);
}
Seat::Seat(Seat&& seat) {
    row_ = seat.row_;
    position_ = seat.position_;
    passenger_ = std::move(seat.passenger_);
}

std::unique_ptr<PassengerOnBoard> Seat::free_seat() {
    passenger_->stand_up();
    return std::move(passenger_);
}

void Seat::take_seat(std::unique_ptr<PassengerOnBoard> passenger) {
    passenger_ = std::move(passenger);
    passenger_->sit();
}

Row::Row(unsigned int row_nr, unsigned int seats_in_row) {
    row_nr_ = row_nr;
    seats_in_row_ = seats_in_row;
    first_lower_seat_ = static_cast<size_t>(seats_in_row_/2 - 1);
    first_higher_seat = static_cast<size_t>(seats_in_row_/2);
    for(unsigned int i = 0; i <seats_in_row_; ++i) {
        seats_.emplace_back(i,seats_in_row);
        buffer_.push_back(nullptr);
        buffer_crossing_counter_.push_back(1U);
    }
}

Row::Row(Row &&row) {
    row_nr_ = row.row_nr_;
    seats_in_row_ = row.seats_in_row_;
    first_lower_seat_ = row.first_lower_seat_;
    first_higher_seat = row.first_higher_seat;
    seats_ = std::move(row.seats_);
    buffer_ = std::move(row.buffer_);
    buffer_crossing_counter_ = std::move(row.buffer_crossing_counter_);
}

void Row::step_forward_row() {
    for(size_t i = 0; i < first_lower_seat_; ++i) {
        // is step forward sensible? Is there someone to take a step, is there free space to stand nad does
        // passenger have a reason to take a step?
        if(buffer_[i] == nullptr && buffer_[i+1] != nullptr &&
                buffer_[i + 1]->get_seat_position() <= static_cast<unsigned int>(i)) {
            // delay of crossing taken seat
            // if passing free seat or was passing time sufficiently long
            if(!seats_[i+1].is_taken() || (seats_[i+1].is_taken() &&
                buffer_crossing_counter_[i+1] == crossing_taken_seat_time)) {
                buffer_[i] = std::move(buffer_[i + 1]);
                buffer_[i + 1] = nullptr;
                buffer_crossing_counter_[i+1] = 1U;
            } else {
                // delay
                ++buffer_crossing_counter_[i+1];
            }
        }
    }
    for(auto i = static_cast<size_t>(seats_in_row_-1); i > first_higher_seat; --i) {
        // same situation but in other half of row - indexes swapped
        if(buffer_[i] == nullptr && buffer_[i-1] != nullptr &&
                buffer_[i - 1]->get_seat_position() >= static_cast<unsigned int>(i)) {
            // delay of crossing taken seat
            if(!seats_[i-1].is_taken() || (seats_[i-1].is_taken() &&
                buffer_crossing_counter_[i-1] == crossing_taken_seat_time)) {
                buffer_[i] = std::move(buffer_[i - 1]);
                buffer_[i - 1] = nullptr;
                buffer_crossing_counter_[i-1] = 1;
            } else {
                ++buffer_crossing_counter_[i-1];
            }
        }
    }
}


bool Row::may_passenger_enter_row(unsigned int row_nr, unsigned int seat_nr) const {
    if (row_nr_ != row_nr) {
        return false;
    }
    if( seat_nr <= static_cast<unsigned int>(first_lower_seat_) && buffer_[first_lower_seat_] != nullptr) {
        return false;
    }
    if( seat_nr >= static_cast<unsigned int>(first_higher_seat) && buffer_[first_higher_seat] != nullptr) {
        return false;
    }
    return true;
}
void Row::enter_row(std::unique_ptr<PassengerOnBoard> passenger) {
    if (passenger->get_seat_row() == row_nr_) {
        if (passenger->get_seat_position() < seats_in_row_ / 2) {
            if (buffer_[first_lower_seat_] == nullptr) {
                buffer_[first_lower_seat_] = std::move(passenger);
            }
        } else {
            if(buffer_[first_higher_seat] == nullptr) {
                buffer_[first_higher_seat] = std::move(passenger);
            }
        }
    }
}

void Row::sit() {
    for(size_t i = 0; i < static_cast<size_t>(seats_in_row_); ++i) {
        if (buffer_[i] == nullptr) {
            continue;
        }
        if (buffer_[i]->get_seat_position() != static_cast<unsigned int>(i)) {
            continue;
        }
        std::unique_ptr<PassengerOnBoard> passenger_ptr = std::move(buffer_[i]);
        passenger_ptr->sit();

        seats_[i].take_seat(std::move(passenger_ptr));
        buffer_[i] = nullptr;

    }
}

