//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_BOARD_HPP
#define PLANE_BOARDING_BOARD_HPP

#include <queue>
#include <functional>
#include <list>
#include "seats.hpp"
#include "passenger.hpp"

enum class QueueAlgorithm {
    BackToFront,
    Wer2

};

class Board {
public:
    Board(int rows_nr, int seats_in_row);

    int get_rows_nr() const { return rows_nr_; }
    int get_seats_nr() const {return seats_nr_; }
    void create_outer_queue(QueueAlgorithm algorithm=QueueAlgorithm::BackToFront);
    int outer_queue_size() const { return static_cast<int>(outer_queue_.size()); }
    int passenger_queued() const;
    std::optional<int> passenger_seat_row_in_aisle(size_t position) const;
    std::optional<bool> passenger_in_aisle_has_luggage(size_t position) const;
    std::string outer_queue_string() const;
    void enqueue_passenger();
    void step_forward();
    void load_luggage();
    void enter_rows();


private:
    int rows_nr_;
    int seats_nr_;
    std::list<Row> rows_;
    std::vector<std::unique_ptr<Passenger>> aisle_;
    std::list<std::unique_ptr<Passenger>> outer_queue_;
};

#endif //PLANE_BOARDING_BOARD_HPP
