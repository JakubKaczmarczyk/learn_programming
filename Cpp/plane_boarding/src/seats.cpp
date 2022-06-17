//
// Created by kubak on 16.06.2022.
//

#include "../include/seats.hpp"

Seat::Seat(Seat &seat) {
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
    for(int i = 0; i < static_cast<int>(seats_in_row); ++i) {
        seats_.push_back(Seat(row_nr_, i));
    }
}

void Row::enter_row(std::unique_ptr<Passenger> passenger) {
    if (passenger->get_seat_row() == row_nr_) {
        if (passenger->get_seat_position() < static_cast<int>(seats_.size()/2)) {
            L_buffer_.push(std::move(passenger));
        } else {
            H_buffer_.push(std::move(passenger));
        }
    }
}

void Row::sit() {
    if(!L_buffer_.empty()) {
        std::unique_ptr<Passenger> passenger = std::move(L_buffer_.top());
        int seat_index = static_cast<int>(passenger->get_seat_position());
        passenger->sit();
        seats_[seat_index].take_seat(std::move(passenger));
        L_buffer_.pop();
    }
    if(!H_buffer_.empty()) {
        std::unique_ptr<Passenger> passenger = std::move(H_buffer_.top());
        int seat_index = static_cast<int>(passenger->get_seat_position());
        passenger->sit();
        seats_[seat_index].take_seat(std::move(passenger));
        H_buffer_.pop();
    }
}

