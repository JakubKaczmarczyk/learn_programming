//
// Created by kubak on 13.06.2022.
//
#include <sstream>
#include <iomanip>
#include "catalogue.hpp"


std::string to_string(const Product& p) {
    std::ostringstream oss;
    oss << p.get_name() << " [" << p.get_id() << "] : $" << std::setprecision(2) << std::fixed << p.get_price();
    return oss.str();
}