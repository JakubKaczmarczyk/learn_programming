//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_PASSENGER_HPP
#define PLANE_BOARDING_PASSENGER_HPP

#include <memory>


class Passenger {
public:
    Passenger(int seat_row, int seat_position) : id_(next_id_), seat_row_(seat_row),
                                                 seat_position_(seat_position), is_sitting_(false),
                                                 loading_luggage_time(1), luggage_in_locker(false) {}

    static void reset_id() {next_id_ = 1; }

    int get_id() const { return id_; }
    int get_seat_row() const { return seat_row_; }
    int get_seat_position() const { return seat_position_; }
    int get_loading_luggage_time() const { return loading_luggage_time; }

    void sit() {is_sitting_ = true; }
    void stand_up() {is_sitting_ = false;}

    void load_luggage() {luggage_in_locker = true;}
    void take_luggage() {luggage_in_locker = false;}

    bool is_sitting() const {return is_sitting_;}

private:
    inline static int next_id_ = 1;
    int id_;
    int seat_row_;
    int seat_position_;
    bool is_sitting_;
    int loading_luggage_time;
    bool luggage_in_locker;

};
#endif //PLANE_BOARDING_PASSENGER_HPP
