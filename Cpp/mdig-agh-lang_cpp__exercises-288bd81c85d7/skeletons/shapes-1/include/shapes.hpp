//
// Created by kubak on 16.06.2022.
//

#ifndef SHAPES_1_SHAPES_HPP
#define SHAPES_1_SHAPES_HPP

const double PI = 3.141592;

class Shape {
public:
    Shape(double x, double y) : x_(x), y_(y) {}
    virtual double area() const = 0;

    virtual ~Shape() = default;
private:
    double x_;
    double y_;
};

class Square : public Shape {
public:
    Square(double x, double y, double side) : Shape(x, y), side_(side) {}
    double area() const override { return side_ * side_;}

    ~Square()=default;
private:
    double side_;
};

class Circle : public Shape {
public:
    Circle(double x, double y, double radius) : Shape(x, y), radius_(radius) {}
    double area() const override { return PI * radius_ * radius_; }

    ~Circle() = default;
private:
    double radius_;
};

#endif //SHAPES_1_SHAPES_HPP
