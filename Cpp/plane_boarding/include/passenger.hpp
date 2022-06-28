//
// Created by kubak on 16.06.2022.
//

#ifndef PLANE_BOARDING_PASSENGER_HPP
#define PLANE_BOARDING_PASSENGER_HPP

#include <memory>

class Passenger {
public:
    Passenger(unsigned int id,
              std::string name,
              std::string surname,
              unsigned int age,
              std::string address,
              std::string city,
              std::string phone_nr,
              bool hand_luggage_registered) :
            id_(id), name_(name), surname_(surname), age_(age), address_(address), city_(city),
            phone_nr_(phone_nr), hand_luggage_registered_(hand_luggage_registered) {}

    // Anonymous passenger
    Passenger() : id_(next_id_), name_(""), surname_(""), age_(40U), address_(""),
    city_(""), phone_nr_(""), hand_luggage_registered_(true) {++next_id_;}

    static void reset_id() { next_id_ = 1; }

    unsigned int get_id() const { return id_; }
    const std::string &getName() const { return name_; }
    const std::string &getSurname() const { return surname_; }
    unsigned int getAge() const { return age_; }
    const std::string &getAddress() const { return address_; }
    const std::string &getCity() const { return city_; }
    const std::string &getPhoneNr() const { return phone_nr_; }
    bool handLuggageRegistered() const { return hand_luggage_registered_; }

private:
    inline static unsigned int next_id_ = 0;
    unsigned int id_;
    std::string name_;
    std::string surname_;
    unsigned int age_;
    std::string address_;
    std::string city_;
    std::string phone_nr_;
    bool hand_luggage_registered_;
};


class PassengerOnBoard {
public:
    // Construct anonymous passenger
    PassengerOnBoard(unsigned int seat_row=0,
                     unsigned int seat_position=0,
                     unsigned int loading_luggage_time=1,
                     unsigned int taking_luggage_time=1,
                     Passenger* passenger_p= nullptr) :
            id_(next_id_),
            seat_row_(seat_row),
            seat_position_(seat_position),
            is_sitting_(false),
            loading_luggage_time_(loading_luggage_time),
            taking_luggage_time_(taking_luggage_time),
            has_luggage_(true),
            luggage_counter_(0),
            passenger_data_(passenger_p)
            {++next_id_;}

    unsigned int get_id() const { return id_; }
    unsigned int get_seat_row() const { return seat_row_; }
    void set_seat_row(unsigned int new_seat_row) { seat_row_ = new_seat_row; }
    unsigned int get_seat_position() const { return seat_position_; }
    void set_seat_position(unsigned int new_seat_position) {seat_position_ = new_seat_position; }
    unsigned int loading_luggage_time() const { return loading_luggage_time_; }
    unsigned int taking_luggage_time() const {return taking_luggage_time_; }
    const Passenger& passenger_data() const {return *passenger_data_; }

    static void reset_id() { next_id_ = 1; }

    void sit() {is_sitting_ = true; }
    void stand_up() {is_sitting_ = false;}

    void load_luggage();
    void take_luggage();

    bool is_sitting() const {return is_sitting_;}
    bool has_luggage() const { return has_luggage_; }

    ~PassengerOnBoard() = default;

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
    Passenger* passenger_data_;

};
#endif //PLANE_BOARDING_PASSENGER_HPP
