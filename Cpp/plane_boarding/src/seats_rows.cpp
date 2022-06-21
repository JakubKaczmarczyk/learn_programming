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

std::unique_ptr<Passenger> Seat::free_seat() {
    passenger_->stand_up();
    return std::move(passenger_);
}

void Seat::take_seat(std::unique_ptr<Passenger> passenger) {
    passenger_ = std::move(passenger);
    passenger_->sit();
}

Row::Row(unsigned int row_nr, unsigned int seats_in_row) {
    row_nr_ = row_nr;
    seats_in_row_ = seats_in_row;
    first_lower_seat_ = static_cast<size_t>(seats_in_row_/2 - 1);
    first_higher_seat = static_cast<size_t>(seats_in_row_/2);
    for(unsigned int i = 0; i <seats_in_row_; ++i) {
        seats_.emplace_back(row_nr_, i);
        buffer_.push_back(nullptr);
    }
}

Row::Row(Row &&row) {
    row_nr_ = row.row_nr_;
    seats_in_row_ = row.seats_in_row_;
    first_lower_seat_ = row.first_lower_seat_;
    first_higher_seat = row.first_higher_seat;
    seats_ = std::move(row.seats_);
    buffer_ = std::move(row.buffer_);
}

void Row::step_forward_row() {
    for(size_t i = 0; i < first_lower_seat_; ++i) {
        if(buffer_[i] == nullptr && buffer_[i+1] != nullptr &&
            buffer_[i+1]->seat_position() <= static_cast<unsigned int>(i)) {
            buffer_[i] = std::move(buffer_[i+1]);
            buffer_[i+1] = nullptr;
        }
    }
    for(auto i = static_cast<size_t>(seats_in_row_-1); i > first_higher_seat; --i) {
        if(buffer_[i] == nullptr && buffer_[i-1] != nullptr &&
        buffer_[i-1]->seat_position() >= static_cast<unsigned int>(i)) {
            buffer_[i] = std::move(buffer_[i-1]);
            buffer_[i-1] = nullptr;
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
void Row::enter_row(std::unique_ptr<Passenger> passenger) {
    if (passenger->seat_row() == row_nr_) {
        if (passenger->seat_position() < seats_in_row_ / 2) {
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
        if (buffer_[i]->seat_position() != static_cast<unsigned int>(i)) {
            continue;
        }
        std::unique_ptr<Passenger> passenger_ptr = std::move(buffer_[i]);
        passenger_ptr->sit();

        seats_[i].take_seat(std::move(passenger_ptr));
        buffer_[i] = nullptr;

    }
//    if(!L_buffer_.empty()) {
//        std::unique_ptr<Passenger> passenger = std::move(L_buffer_.top());
//        size_t seat_index = static_cast<size_t>(passenger->seat_position());
//        passenger->sit();
//        seats_[seat_index].take_seat(std::move(passenger));
//        L_buffer_.pop();
//    }
//    if(!H_buffer_.empty()) {
//        std::unique_ptr<Passenger> passenger = std::move(H_buffer_.top());
//        size_t seat_index = static_cast<size_t>(passenger->seat_position());
//        passenger->sit();
//        seats_[seat_index].take_seat(std::move(passenger));
//        H_buffer_.pop();
//    }
}

