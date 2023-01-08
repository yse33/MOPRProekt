#include "point.h"

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }

    return *this;
}

bool Point::operator==(const Point& other) {
    return this->x == other.x && this->y == other.y;
}

Point& Point::operator+(const Point& other) {
    this->x += other.x;
    this->y += other.y;
}

//izchislqva raztoqnieto mejdu dve tochki chrez Pitagovorovata teorema
double Point::distance_to_point(const Point& point) const {
    double distance_x = x - point.x;
    double distance_y = y - point.y;
    return sqrt((distance_x * distance_x) + (distance_y * distance_y));
}
