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
    Row(Row&& row);

    int row_nr() const { return row_nr_; }
    int seats_nr() const { return static_cast<int>(seats_.size()); }

    const std::vector<Seat>& seat() const {return seats_; }
    const std::vector<std::unique_ptr<Passenger>>& buffer() const { return buffer_; }

    void step_forward_row();
    bool may_passenger_enter_row(int row_nr, int seat_nr) const;
    void enter_row(std::unique_ptr<Passenger> passenger);
    void sit();



private:
    int row_nr_;
    int seats_in_row_;
    size_t first_lower_seat_;
    size_t first_higher_seat;
    std::vector<Seat> seats_;
    std::vector<std::unique_ptr<Passenger>> buffer_;

};

#endif //PLANE_BOARDING_SEATS_HPP
