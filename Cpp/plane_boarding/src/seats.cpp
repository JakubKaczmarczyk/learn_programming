//
// Created by kubak on 16.06.2022.
//

#include "../include/seats.hpp"

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

Row::Row(int row_nr, int seats_in_row) {
    row_nr_ = row_nr;
    seats_in_row_ = seats_in_row;
    first_lower_seat_ = static_cast<size_t>(seats_in_row_/2 - 1);
    first_higher_seat = static_cast<size_t>(seats_in_row_/2);
    for(int i = 0; i <seats_in_row_; ++i) {
        seats_.push_back(Seat(row_nr_, i));
        buffer_.push_back(nullptr);
    }
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

