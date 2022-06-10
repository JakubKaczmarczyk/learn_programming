#include <iostream>

class Circle {
public:
    Circle(double r) { radius_ = r; };
    double area() { return 3.14 * radius_ * radius_; }
private:
    double radius_;
};
int main() {
    Circle kolo1(2.0);
    std::cout << kolo1.area() << std::endl;
    return 0;
}
