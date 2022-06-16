#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "vehicles.hpp"

using ::testing::Property;

TEST(CarTest, get_max_speed) {
    Car car("1", "Audi",100.0);
    ASSERT_EQ(car.get_max_speed(), 100.0);
}

TEST(BicycleTest, get_max_speed) {
    Bicycle bicycle("1", "Kross",9*3);
    ASSERT_EQ(bicycle.get_max_speed(), 9*3*3);
}

TEST(VehicleTest, to_string_car) {
    Car car("1", "Audi",100.0);
    EXPECT_EQ(to_string(car), "1 : Audi");
}

TEST(VehicleTest, to_string_bic) {
    Bicycle bicycle("1", "Kross",9*3);
    EXPECT_EQ(to_string(bicycle), "1 : Kross");
}

TEST(CarTest, travel_time) {
    Car car("1", "Audi", 40.0);
    EXPECT_EQ(compute_min_travel_duration(80.0, car), 2.0);
}

TEST(BicycleTest, travel_time) {
    Bicycle bicycle("1", "Kross",10);
    EXPECT_EQ(compute_min_travel_duration(15.0, bicycle), 0.5);
}

TEST(VehicleAuxTest, computeMinTravelDurationAsString) {
    Car car("", "", 100.0);
    Bicycle bike("", "", 8);

    double distance = 50;
    std::string result_car = compute_min_travel_duration_as_string(distance, car);
    std::string result_bicycle = compute_min_travel_duration_as_string(distance, bike);

    EXPECT_EQ(result_car, "0.500 h");
    EXPECT_EQ(result_bicycle, "2.083 h");
}

TEST(VehicleAuxTest, filter) {
    Car car1("C1", "", 100.0);
    Car car2("C2", "", 200.0);
    Bicycle bicycle("B1", "", 1);

    std::vector<Vehicle*> vehicles = {&car1, &bicycle, &car2};
    std::function<bool(const Vehicle&)> faster_than_50kph = [](const Vehicle& vehicle) {
        return vehicle.get_max_speed() > 50;
    };
    auto filtered_vehicles = filter_vehicles(std::begin(vehicles), std::end(vehicles), faster_than_50kph);

    ASSERT_EQ(filtered_vehicles.size(), 2U);
    EXPECT_THAT(filtered_vehicles, Contains(Property(&Vehicle::get_id, car1.get_id())));
    EXPECT_THAT(filtered_vehicles, Contains(Property(&Vehicle::get_id, car2.get_id())));
}