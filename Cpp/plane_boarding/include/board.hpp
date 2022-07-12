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
    EvenWindows
};


enum class LuggageTime {
    Random,
    Fixed
};


class Board {
public:
    // Constructors
    Board(unsigned int rows_nr, unsigned int seats_in_row);

    // Get info about board
    unsigned int get_rows_nr() const { return rows_nr_; }
    unsigned int get_seats_nr() const {return seats_nr_; }
    const std::vector<Row>& rows() const {return rows_; }
    const std::vector<std::unique_ptr<PassengerOnBoard>>& aisle() const { return aisle_; }
    const std::vector<std::unique_ptr<PassengerOnBoard>>& outer_queue() const {return outer_queue_; }

    // Luggage time settings
    void set_luggage_time_settings(LuggageTime luggage_time_type, unsigned int manage_luggage_time,
                                   unsigned int max_time, unsigned int min_time);
    // Creating board: DB or anonymous
    void create_board_plan_anonymous();
    void create_board_plan_from_database(std::string host, std::string user, std::string password, std::string database);

    // Create queue
    void create_outer_queue(QueueAlgorithm algorithm);
    std::string outer_queue_string() const;

    // Simulation actions
    void enqueue_passenger();
    void step_forward();
    void load_luggage();
    void enter_rows();
    void step_forward_row();
    void sit();
    bool is_boarding_finished() const;

    // reports
    void clear_report(const std::string& report_file_name) ;
    void generate_tour_report(unsigned int turn, const std::string& report_file_name) const ;

private:
    // Methods:
    // generating luggage managing time
    unsigned int luggage_time() const;

    // Queue algorithms
    void back_to_front_queue();
    void front_to_back_queue();
    void wiki_queue();
    void even_windows_queue();

    // Attributes
    unsigned int rows_nr_;
    unsigned int seats_nr_;
    std::vector<Row> rows_;
    std::vector<std::unique_ptr<PassengerOnBoard>> aisle_;
    std::vector<std::unique_ptr<PassengerOnBoard>> outer_queue_;
    std::vector<std::vector<Passenger>> board_plan_;

    // time attributes
    unsigned int fixed_manage_luggage_time_ = 2U;
    unsigned int random_luggage_max_time_ = 4U;
    unsigned int random_luggage_min_time_ = 1U;
    bool random_luggage_time_ = false;
};



#endif //PLANE_BOARDING_BOARD_HPP
