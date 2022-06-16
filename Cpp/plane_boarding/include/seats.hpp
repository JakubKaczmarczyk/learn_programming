//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_SEATS_HPP
#define PLANE_BOARDING_SEATS_HPP

#include "passenger.hpp"
#include <vector>
#include <memory>
#include <stack>

class Seat {
public:
    Seat(int position, int row) : position_(position), row_(row) {}

    bool is_taken() const { return is_taken_;}
    std::unique_ptr<Passenger> free_seat() { is_taken_ = false; return std::move(passenger_);}
    void take_seat(std::unique_ptr<Passenger> passenger);

    int get_position() const { return position_; }
    int get_row() const { return row_;}

    ~Seat() = default;

private:
    bool is_taken_ = false;
    int position_;
    int row_;
    std::unique_ptr<Passenger> passenger_ = nullptr;

};

class Row {
public:
    Row(int seats_in_row, int row_nr) : size_(seats_in_row), row_nr_(row_nr) {}

    int size() const { return size_;}

    const Seat& operator[](std::size_t position) const { return seats_[position]; }
    Seat& operator[](std::size_t position) { return seats_[position]; }

    void enter_row(std::unique_ptr<Passenger> passenger);
//    std::unique_ptr<Passenger> leave_row();


private:
    int size_;
    int row_nr_;
    std::vector<Seat> seats_;
    std::stack<Seat> L_buffer_;
    std::stack<Seat> R_buffer_;
};


#endif //PLANE_BOARDING_SEATS_HPP
