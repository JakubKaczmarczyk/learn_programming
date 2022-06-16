//
// Created by kubak on 16.06.2022.
//

#include "board.hpp"


//Board::Board(int row_number, int seats_in_row) {
//    for(int i = 0; i < row_number; ++i) {
//        rows_.push_back(Row(seats_in_row));
//        aisle_.push_back(nullptr);
//    }
//}

//void Board::step_forward() {
//    for(int j = static_cast<int>(aisle_.size())-2; j >= 0; --j) {
//        int i = static_cast<size_t>(j);
//        if (aisle_[i] != nullptr && aisle_[i+1] == nullptr) {
//            aisle_[i+1] = aisle_[i];
//            aisle_[i] = nullptr;
//        }
//    }
//}
//
//void Board::enqueue_p(std::shared_ptr<Passenger> passenger_ptr) {
//    if (aisle_[0] == nullptr) {
//        aisle_[0] = passenger_ptr;
//    }
//}
//
//void Board::sit() {
//    for(size_t i = 0; i < aisle_.size(); ++i) {
//        if (aisle_[i] != nullptr && aisle_[i]->get_seat_row() == static_cast<int>(i)) {
//            aisle_[i]->take_seat();
//            aisle_[i] = nullptr;
//        }
//    }
//}
//
//bool Board::are_all_seats_taken() const {
//    for(const auto& row : rows_) {
//        for (const auto& seat : row) {
//            if (!(seat->is_taken())) {
//                return false;
//            }
//
//        }
//    }
//    return true;
//}