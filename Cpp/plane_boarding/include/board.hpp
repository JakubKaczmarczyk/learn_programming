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
    Board(unsigned int rows_nr, unsigned int seats_in_row);

    unsigned int rows_nr() const { return rows_nr_; }
    unsigned int seats_nr() const {return seats_nr_; }
    const std::vector<Row>& rows() const {return rows_; }
    const std::vector<std::unique_ptr<Passenger>>& aisle() const { return aisle_; }
    const std::vector<std::unique_ptr<Passenger>>& outer_queue() const {return outer_queue_; }
    void create_outer_queue(QueueAlgorithm algorithm, LuggageTime luggage_time_type, unsigned int manage_luggage_time,
                            unsigned int max_time, unsigned int min_time);
    std::string outer_queue_string() const;
    void enqueue_passenger();
    void step_forward();
    void load_luggage();
    void enter_rows();
    void step_forward_row();
    void sit();
    bool is_boarding_finished() const;
    // reports
    void clear_report(const std::string& report_file_name) ;
    void generate_tour_report(int turn, const std::string& report_file_name) const ;

private:
    unsigned int luggage_time() const;
    void back_to_front_queue();
    void front_to_back_queue();
    void wiki_queue();
    void even_windows_queue();

    unsigned int rows_nr_;
    unsigned int seats_nr_;
    std::vector<Row> rows_;
    std::vector<std::unique_ptr<Passenger>> aisle_;
    std::vector<std::unique_ptr<Passenger>> outer_queue_;

    unsigned int fixed_manage_luggage_time_ = 2U;
    unsigned int random_luggage_max_time_ = 4U;
    unsigned int random_luggage_min_time_ = 1U;
    bool random_luggage_time = false;


};

// Report helpers functions
size_t digit_nr(unsigned int nr);
size_t digit_max_index_nr(unsigned int nr);
size_t get_position_width(const Board& board);
std::string position_correct_width(unsigned int act_row, unsigned int rows_nr, unsigned int act_seat, unsigned int seats_nr);
std::string upper_line(const Board& board);
std::string line_passenger(const Board& board, unsigned int line_nr);
std::string queue_aisle_line(const Board& board);

#endif //PLANE_BOARDING_BOARD_HPP
