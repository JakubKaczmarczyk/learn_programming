//
// Created by kubak on 13.06.2022.
//
#include <sstream>
#include<string.h>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <clocale>
#include "catalogue.hpp"


std::string to_string(const Product& p) {
    std::ostringstream oss;
    oss << p.get_name() << " [" << p.get_id() << "] : $" << std::setprecision(2) << std::fixed << p.get_price();
    return oss.str();
}

std::vector<Product> Catalogue::get_products_with_appropriate_price(std::function<bool(double)> choose_fun) const {
    std::vector<Product> filtered_products;
    for(const auto& [key, product] : inventory_) {
        if (choose_fun(product.get_price())) {
            filtered_products.push_back(product);
        }
    }
    return filtered_products;
}

std::vector<Product> Catalogue::get_products_by_name_part(std::string substr, bool is_case_sensitive) const {
    std::vector<Product> filtered_products;
    std::string str_to_look_for = substr;

    if(!is_case_sensitive) {
        std::string str_to_look_for_trans = substr;
        std::transform(str_to_look_for.begin(), str_to_look_for.end(), str_to_look_for_trans.begin(), ::tolower);
        str_to_look_for = str_to_look_for_trans;
    }

    for(const auto& [key, product] : inventory_) {
        std::string name = product.get_name();
        if(!is_case_sensitive) {
            std::string name_transformed = name;
            std::transform(name.cbegin(), name.cend(), name_transformed.begin(), ::tolower);
            name = name_transformed;
        }

        if (name.find(str_to_look_for) != std::string::npos) {
            filtered_products.push_back(product);
        }
    }

    return filtered_products;
}