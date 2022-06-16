//
// Created by kubak on 16.06.2022.
//

#include "../include/seats.hpp"


void Seat::take_seat(std::unique_ptr<Passenger> passenger) {
    is_taken_ = true;
    passenger_ = std::move(passenger);
}


