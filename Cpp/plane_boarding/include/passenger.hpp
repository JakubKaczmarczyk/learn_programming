//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_PASSENGER_HPP
#define PLANE_BOARDING_PASSENGER_HPP

#include <memory>


class Passenger {
public:
    Passenger(unsigned int seat_row, unsigned int seat_position, unsigned int loading_luggage_time=1,
              unsigned int taking_luggage_time=1) :
            id_(next_id_), seat_row_(seat_row),
            seat_position_(seat_position),
            is_sitting_(false),
            loading_luggage_time_(loading_luggage_time),
            taking_luggage_time_(taking_luggage_time),
            has_luggage_(true),
            luggage_counter_(0) {++next_id_; }

    static void reset_id() { next_id_ = 1; }

    unsigned int get_id() const { return id_; }
    unsigned int seat_row() const { return seat_row_; }
    unsigned int seat_position() const { return seat_position_; }
    unsigned int loading_luggage_time() const { return loading_luggage_time_; }
    unsigned int taking_luggage_time() const {return taking_luggage_time_; }

    void sit() {is_sitting_ = true; }
    void stand_up() {is_sitting_ = false;}

    void load_luggage();
    void take_luggage();

    bool is_sitting() const {return is_sitting_;}
    bool has_luggage() const { return has_luggage_; }

    ~Passenger() = default;

private:
    inline static unsigned int next_id_ = 1;
    unsigned int id_;
    unsigned int seat_row_;
    unsigned int seat_position_;
    bool is_sitting_;
    unsigned int loading_luggage_time_;
    unsigned int taking_luggage_time_;
    bool has_luggage_;
    unsigned int luggage_counter_;

};
#endif //PLANE_BOARDING_PASSENGER_HPP
