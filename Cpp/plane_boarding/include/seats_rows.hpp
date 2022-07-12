//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_SEATS_ROWS_HPP
#define PLANE_BOARDING_SEATS_ROWS_HPP

#include "passenger.hpp"
#include <vector>
#include <memory>
#include <stack>

class Seat {
public:
    Seat(unsigned int row, unsigned int position) : row_(row), position_(position)  {}
    Seat(Seat& seat);
    Seat(Seat&& seat);

    ~Seat() = default;

    // getters seat info
    unsigned int get_position() const { return position_; }
    unsigned int get_row() const { return row_;}
    bool is_taken() const { return passenger_ != nullptr;}

    // Simulation actions
    std::unique_ptr<PassengerOnBoard> free_seat();
    void take_seat(std::unique_ptr<PassengerOnBoard> passenger);

private:
    unsigned int row_;
    unsigned int position_;
    std::unique_ptr<PassengerOnBoard> passenger_ = nullptr;
};

class Row {
public:
    Row(unsigned int row_nr, unsigned int seats_in_row);
    Row(Row&& row);

    ~Row() = default;

    // getters row info
    unsigned int get_row_nr() const { return row_nr_; }
    unsigned int get_seats_nr() const { return seats_in_row_; }
    const std::vector<Seat>& seat() const {return seats_; }
    const std::vector<std::unique_ptr<PassengerOnBoard>>& buffer() const { return buffer_; }

    // simulation actions
    void step_forward_row();
    bool may_passenger_enter_row(unsigned int row_nr, unsigned int seat_nr) const;
    void enter_row(std::unique_ptr<PassengerOnBoard> passenger);
    void sit();

private:
    unsigned int row_nr_;
    unsigned int seats_in_row_;
    size_t first_lower_seat_;
    size_t first_higher_seat;
    std::vector<Seat> seats_;
    std::vector<std::unique_ptr<PassengerOnBoard>> buffer_;
    std::vector<unsigned int> buffer_crossing_counter_;
    unsigned int crossing_taken_seat_time = 2;

};

#endif //PLANE_BOARDING_SEATS_ROWS_HPP
