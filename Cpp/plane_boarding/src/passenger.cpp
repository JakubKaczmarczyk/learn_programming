//
// Created by kubak on 16.06.2022.
//

#include "passenger.hpp"

void Passenger::load_luggage() {
    if (has_luggage_) {
        ++luggage_counter_;
        if (luggage_counter_ == loading_luggage_time_) {
            luggage_counter_ = 0;
            has_luggage_ = false;
        }
    }
}

void Passenger::take_luggage() {
    if (!has_luggage_) {
        ++luggage_counter_;
        if (luggage_counter_ == taking_luggage_time_) {
            luggage_counter_ = 0;
            has_luggage_ = true;
        }
    }
}

