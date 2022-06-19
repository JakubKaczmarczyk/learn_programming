//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_PASSENGER_HPP
#define PLANE_BOARDING_PASSENGER_HPP

#include <memory>


class Passenger {
public:
    Passenger(int seat_row, int seat_position, int loading_luggage_time=1, int taking_luggage_time=1) :
            id_(next_id_), seat_row_(seat_row),
            seat_position_(seat_position),
            is_sitting_(false),
            loading_luggage_time_(loading_luggage_time),
            taking_luggage_time_(taking_luggage_time),
            has_luggage_(true),
            luggage_counter_(0) {++next_id_; }

    static void reset_id() { next_id_ = 1; }

    int get_id() const { return id_; }
    int seat_row() const { return seat_row_; }
    int seat_position() const { return seat_position_; }
    int loading_luggage_time() const { return loading_luggage_time_; }
    int taking_luggage_time() const {return taking_luggage_time_; }

    void sit() {is_sitting_ = true; }
    void stand_up() {is_sitting_ = false;}

    void load_luggage();
    void take_luggage();

    bool is_sitting() const {return is_sitting_;}
    bool has_luggage() const { return has_luggage_; }

    ~Passenger() = default;

private:
    inline static int next_id_ = 1;
    int id_;
    int seat_row_;
    int seat_position_;
    bool is_sitting_;
    int loading_luggage_time_;
    int taking_luggage_time_;
    bool has_luggage_;
    int luggage_counter_;

};
#endif //PLANE_BOARDING_PASSENGER_HPP
