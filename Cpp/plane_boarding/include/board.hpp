//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_BOARD_HPP
#define PLANE_BOARDING_BOARD_HPP

#include <functional>
#include "seats_rows.hpp"
#include "passenger.hpp"

enum class QueueAlgorithm {
    BackToFront,
    FrontToBack,
    Wiki,

};

class Board {
public:
    Board(unsigned int rows_nr, unsigned int seats_in_row);

    unsigned int rows_nr() const { return rows_nr_; }
    unsigned int seats_nr() const {return seats_nr_; }
    const std::vector<Row>& rows() const {return rows_; }
    const std::vector<std::unique_ptr<Passenger>>& aisle() const { return aisle_; }
    const std::vector<std::unique_ptr<Passenger>>& outer_queue() const {return outer_queue_; }
    void create_outer_queue(QueueAlgorithm algorithm=QueueAlgorithm::BackToFront);


    std::string outer_queue_string() const;
    void enqueue_passenger();
    void step_forward();
    void load_luggage();
    void enter_rows();
    void step_forward_row();
    void sit();
    bool is_boarding_finished() const;


    // raports
    void clear_report(std::string name) const;
    void generate_tour_report(int turn, std::string name) const ;






private:
    unsigned int rows_nr_;
    unsigned int seats_nr_;
    std::vector<Row> rows_;
    std::vector<std::unique_ptr<Passenger>> aisle_;
    std::vector<std::unique_ptr<Passenger>> outer_queue_;
};

size_t get_position_width(const Board& board);
std::string upper_line(const Board& board);
std::string line_passenger(const Board& board, unsigned int line_nr);

#endif //PLANE_BOARDING_BOARD_HPP
