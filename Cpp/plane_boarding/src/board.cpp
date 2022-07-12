//
// Created by kubak on 16.06.2022.
//

#include "board.hpp"
#include <sstream>
#include <string>
#include <fstream>

#include <limits>
#include <ctime>
#include "mysql.h"
#include <iostream>


Board::Board(unsigned int rows_nr, unsigned int seats_in_row) {
    if(seats_in_row%2 != 0) {
        throw std::logic_error("Not even seats");
    }
    rows_nr_ = rows_nr;
    seats_nr_ = seats_in_row;
    for(unsigned int i = 0; i < rows_nr; ++i) {
        rows_.emplace_back(i, seats_nr_);
        aisle_.push_back(nullptr);
        board_plan_.push_back(std::vector<Passenger>());
    }
    for(unsigned int i = 0; i < rows_nr_*seats_nr_; ++i) {
        outer_queue_.push_back(nullptr);
    }
}

void Board::create_board_plan_anonymous() {
    for(unsigned int row_it=0; row_it < rows_nr_; ++row_it) {
        for(unsigned int seat_it=0; seat_it < seats_nr_; ++seat_it) {
            board_plan_[row_it].push_back(Passenger());
        }
    }
}

void Board::create_board_plan_from_database(std::string host, std::string user, std::string password, std::string database) {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 3306, NULL, 0);

    if(!conn) {
        std::cout << "Cannot connect with database" << std::endl;
    }
    std::cout << "Successfully connected to database" << std::endl;

    std::string query = "SELECT * FROM passengers";
    const char * query_c = query.c_str();
    bool qstate = false;
    qstate = mysql_query(conn, query_c);
    if(!qstate) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);

        // temporary variables to cast types and create Passenger instance
        unsigned int id;
        std::string name;
        std::string surname;
        unsigned int age;
        std::string address;
        std::string city;
        std::string phone_nr;
        bool hand_luggage_registered;

        for(unsigned int row_it=0; row_it < rows_nr_; ++row_it) {
            for(unsigned int seat_it=0; seat_it < seats_nr_; ++seat_it) {

                std::stringstream(row[0]) >> id;
                name = std::string(row[1]);
                surname = std::string(row[2]);
                std::stringstream(row[3]) >> age;
                address = std::string(row[4]);
                city = std::string(row[5]);
                phone_nr = std::string(row[6]);
                std::stringstream(row[7]) >> hand_luggage_registered;

                board_plan_[row_it].push_back(Passenger(id, name, surname, age, address, city, phone_nr, hand_luggage_registered));
                bool xd = row[1] == row[2];
                xd = !xd;
                row = mysql_fetch_row(res);
            }
        }
    }
}

void Board::set_luggage_time_settings(LuggageTime luggage_time_type, unsigned int manage_luggage_time,
                               unsigned int max_time, unsigned int min_time) {
    random_luggage_time_ = luggage_time_type == LuggageTime::Random;
    fixed_manage_luggage_time_ = manage_luggage_time;
    random_luggage_max_time_ = max_time;
    random_luggage_min_time_ = min_time;
    srand(static_cast<unsigned int>(time(NULL)));
}

void Board::create_outer_queue(QueueAlgorithm algorithm) {
    switch (algorithm) {
        case QueueAlgorithm::BackToFront: {
            back_to_front_queue();
            break;
        }
        case QueueAlgorithm::FrontToBack: {
            front_to_back_queue();
            break;
        }

        case QueueAlgorithm::Wiki: {
            wiki_queue();
            break;
        }

        case QueueAlgorithm::EvenWindows: {
            even_windows_queue();
            break;
        }
        default: {
            break;
        }
    }
}

unsigned int Board::luggage_time() const {
    if(random_luggage_time_) {
        return static_cast<unsigned int>(rand()) % (random_luggage_max_time_ - random_luggage_min_time_ + 1) + random_luggage_min_time_;
    } else {
        return fixed_manage_luggage_time_;
    }
}

void Board::back_to_front_queue() {
    std::vector<unsigned int> seats_numbers;
    for(unsigned int i = 0; i < seats_nr_/2; ++i) {
        seats_numbers.push_back(i);
    }
    for(unsigned int i = seats_nr_-1; i >= seats_nr_/2; --i) {
        seats_numbers.push_back(i);
    }
    auto queue_it = static_cast<size_t>(rows_nr_*seats_nr_-1);
    for (unsigned int row_it = rows_nr_ - 1; row_it != std::numeric_limits<unsigned int>::max(); --row_it) {
        for (auto seat_it : seats_numbers) {
            outer_queue_[queue_it] = std::make_unique<PassengerOnBoard>(row_it, seat_it, luggage_time(), luggage_time(),&board_plan_[row_it][seat_it]);
            --queue_it;
        }
    }
}

void Board::front_to_back_queue() {
    std::vector<unsigned int> seats_numbers;
    for(unsigned int i = 0; i < seats_nr_/2; ++i) {
        seats_numbers.push_back(i);
    }
    for(unsigned int i = seats_nr_-1; i >= seats_nr_/2; --i) {
        seats_numbers.push_back(i);
    }
    auto queue_it = static_cast<size_t>(rows_nr_*seats_nr_-1);
    for (unsigned int row_it = 0; row_it < rows_nr_; ++row_it) {
        for (auto seat_it : seats_numbers) {
            outer_queue_[queue_it] = std::make_unique<PassengerOnBoard>(row_it, seat_it, luggage_time(), luggage_time(),&board_plan_[row_it][seat_it]);
            --queue_it;
        }
    }
}

void Board::wiki_queue() {
    auto queue_it = static_cast<size_t>(rows_nr_*seats_nr_-1);
    std::vector<unsigned int> seats_numbers;
    unsigned int down_it = 0U;
    unsigned int up_it = seats_nr_-1;
    while (down_it<up_it) {
        seats_numbers.push_back(down_it);
        seats_numbers.push_back(up_it);
        ++down_it;
        --up_it;
    }
    for (auto const &seat_it: seats_numbers) {
        for (unsigned int row_it = rows_nr_ - 1; row_it != std::numeric_limits<unsigned int>::max(); --row_it) {
            outer_queue_[queue_it] = std::make_unique<PassengerOnBoard>(row_it, seat_it, luggage_time(), luggage_time(), &board_plan_[row_it][seat_it]);
            --queue_it;
        }
    }
}

void Board::even_windows_queue() {
    auto queue_it = static_cast<size_t>(rows_nr_*seats_nr_-1);
    std::vector<std::pair<unsigned int, unsigned int>> seats_pairs;
    unsigned int down_it = 0U;
    unsigned int up_it = seats_nr_-1;
    while (down_it<up_it) {
        seats_pairs.emplace_back(down_it, up_it);
        ++down_it;
        --up_it;
    }
    for(auto& pair_it : seats_pairs) {
        unsigned int lower_sit = pair_it.first;
        unsigned int upper_sit = pair_it.second;
        for(unsigned int row_it = rows_nr_ - 1;
            (row_it != std::numeric_limits<unsigned int>::max() &&
             row_it != std::numeric_limits<unsigned int>::max() -1);
            row_it = row_it - 2) {
            outer_queue_[queue_it] = std::make_unique<PassengerOnBoard>(row_it, lower_sit, luggage_time(), luggage_time(), &board_plan_[row_it][lower_sit]);
            --queue_it;
        }
        for(unsigned int row_it = rows_nr_ - 1;
            (row_it != std::numeric_limits<unsigned int>::max() &&
             row_it != std::numeric_limits<unsigned int>::max() -1);
            row_it = row_it - 2) {
            outer_queue_[queue_it] = std::make_unique<PassengerOnBoard>(row_it, upper_sit, luggage_time(), luggage_time(), &board_plan_[row_it][upper_sit]);
            --queue_it;
        }
        for (unsigned int row_it = rows_nr_ - 2;
             (row_it != std::numeric_limits<unsigned int>::max() &&
              row_it != std::numeric_limits<unsigned int>::max() - 1);
             row_it = row_it - 2) {
            outer_queue_[queue_it] = std::make_unique<PassengerOnBoard>(row_it, lower_sit, luggage_time(), luggage_time(), &board_plan_[row_it][lower_sit]);
            --queue_it;
        }
        for (unsigned int row_it = rows_nr_ - 2;
             (row_it != std::numeric_limits<unsigned int>::max() &&
              row_it != std::numeric_limits<unsigned int>::max() - 1);
             row_it = row_it - 2) {
            outer_queue_[queue_it] = std::make_unique<PassengerOnBoard>(row_it, upper_sit, luggage_time(), luggage_time(), &board_plan_[row_it][upper_sit]);
            --queue_it;
        }
    }
}

std::string Board::outer_queue_string() const {
    std::ostringstream oss;
    for(const auto& passenger : outer_queue_) {
        oss << "(" << passenger->get_seat_row() << " " << passenger->get_seat_position() << ")\n";
    }
    return oss.str();

}

void Board::enqueue_passenger() {
    if (aisle_[0] != nullptr) {
        return;
    }
    if (outer_queue_[static_cast<size_t>(rows_nr_*seats_nr_-1)] == nullptr) {
        return;
    }
    aisle_[0] = std::move(outer_queue_[static_cast<size_t>(rows_nr_*seats_nr_-1)]);
    outer_queue_.pop_back();
    outer_queue_.insert(outer_queue_.begin(), nullptr);
}

void Board::step_forward() {
    for(auto i = static_cast<size_t>(rows_nr_-1); i >= 1; --i) {
        if (aisle_[i-1] != nullptr && aisle_[i] == nullptr &&
                aisle_[i - 1]->get_seat_row() != static_cast<unsigned int>(i - 1)) {
            aisle_[i] = std::move(aisle_[i-1]);
            aisle_[i-1] = nullptr;
        }
    }
}



void Board::load_luggage() {
    for(size_t i = 0; i < aisle_.size(); ++i) {
        if (aisle_[i] == nullptr) {
            continue;
        }
        if (aisle_[i]->get_seat_row() != static_cast<unsigned int>(i) ) {
            continue;
        }
        aisle_[i] -> load_luggage();
    }
}

void Board::enter_rows() {
    std::vector<bool> may_enter_row(static_cast<size_t>(rows_nr_), false);
    for(size_t i = 0; i < static_cast<size_t>(rows_nr_); ++i) {
        if (aisle_[i] != nullptr) {
            may_enter_row[i] = rows_[i].may_passenger_enter_row(
                    aisle_[i]->get_seat_row(), aisle_[i]->get_seat_position());
        }
    }
    for(size_t i = 0; i < static_cast<size_t>(rows_nr_); ++i) {
        if (aisle_[i] == nullptr) {
            continue;
        }
        if (aisle_[i]->has_luggage()) {
            continue;
        }
        if (!may_enter_row[i]) {
            continue;
        }
        rows_[i].enter_row(std::move(aisle_[i]));
        aisle_[i] = nullptr;

    }
}

void Board::step_forward_row() {
    for(auto& row : rows_) {
        row.step_forward_row();
    }

}
void Board::sit() {
    for(auto& row : rows_) {
        row.sit();
    }
}

bool Board::is_boarding_finished() const {
    for(auto& row : rows_) {
        for(size_t i = 0; i < static_cast<size_t>(seats_nr_); ++i) {
            if( !row.seat()[i].is_taken() ) {
                return false;
            }
        }
    }
    return true;
}
