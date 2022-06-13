//
// Created by kubak on 13.06.2022.
//

#ifndef CATALOGUE_1_CATALOGUE_HPP
#define CATALOGUE_1_CATALOGUE_HPP

#include <string>
#include <map>

class Product {
public:
    Product(std::string id, std::string name, double price) : id_(id), name_(name), price_(price) {};

    std::string get_id() const {return id_; }
    std::string get_name() const {return name_; }
    double get_price() const {return price_; }

private:
    std::string id_;
    std::string name_;
    double price_;
};

std::string to_string(const Product& p);

class Catalogue {
public:
    using inventory_t = std::map<std::string, Product>;

    Catalogue(const inventory_t& inventory = inventory_t{}) : inventory_(inventory) {}
    void add_product(Product& product) { inventory_.emplace(product.get_id(), product); }
    bool contains(std::string id) const { return inventory_.find(id) != inventory_.end(); }

private:
    inventory_t inventory_;
};
#endif //CATALOGUE_1_CATALOGUE_HPP
