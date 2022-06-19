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
    Seat(int row, int position) : row_(row), position_(position)  {}
    Seat(Seat& seat);
    Seat(Seat&& seat);

    bool is_taken() const { return passenger_ != nullptr;}
    std::unique_ptr<Passenger> free_seat();
    void take_seat(std::unique_ptr<Passenger> passenger);

    int get_position() const { return position_; }
    int get_row() const { return row_;}

    ~Seat() = default;

private:
    int row_;
    int position_;
    std::unique_ptr<Passenger> passenger_ = nullptr;

};

class Row {
public:
    Row(int row_nr, int seats_in_row);
//    Row(Row&& row);

    int row_nr() const { return row_nr_; }
    int seats_nr() const { return static_cast<int>(seats_.size()); }
//    int L_buffer_size() const { return static_cast<int>(L_buffer_.size()); }
//    int H_buffer_size() const { return static_cast<int>(H_buffer_.size()); }

    const Seat& operator[](std::size_t position) const { return seats_[position]; }
    Seat& operator[](std::size_t position) { return seats_[position]; }

//    bool may_passenger_enter_row(std::unique_ptr<)
    void enter_row(std::unique_ptr<Passenger> passenger);
    void sit();
//    std::unique_ptr<Passenger> leave_row();


private:
    int row_nr_;
    int seats_in_row_;
    size_t first_lower_seat_;
    size_t first_higher_seat;
    std::vector<Seat> seats_;
    std::vector<std::unique_ptr<Passenger>> buffer_;
//    std::stack<std::unique_ptr<Passenger>> L_buffer_;
//    std::stack<std::unique_ptr<Passenger>> H_buffer_;
};

#endif //PLANE_BOARDING_SEATS_HPP
