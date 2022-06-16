//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_BOARD_HPP
#define PLANE_BOARDING_BOARD_HPP

#include <queue>
#include <functional>
#include "seats.hpp"
#include "passenger.hpp"


class Board {
public:
    Board(int rows_nr, int seats_in_row);
    void enqueue(std::function<std::queue<std::unique_ptr<Passenger>>(int,int)>);
    void enqueue_passenger();
    void load_luggage();
    void enter_row();
    void step_forward();
    bool all_seats_are_taken();

private:
    int size_;
    std::vector<Row> rows_;
    std::vector<std::unique_ptr<Passenger>> aisle_;
    std::queue<std::unique_ptr<Passenger>> outer_queue_;
};

#endif //PLANE_BOARDING_BOARD_HPP
