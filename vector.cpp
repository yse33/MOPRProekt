#include "vector.h"

Vector::Vector(const Point& p1, const Point& p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
}

//umnojava vektor po dadeno chislo
void Vector::times_num(double num) {
    x *= num;
    y *= num;
}

//skalarno proizvedenie na dva vektora
double Vector::dot_product(const Vector& other) const {
    return (this->x * other.x) + (this->y * other.y);
}

//proverqva dali 2 vektora sa kolinearni
bool Vector::is_colinear(const Vector& other) const {
    return this->x * other.y == this->y * other.x;
}

//vrushta duljinata na vektora
double Vector::length() const {
    return sqrt(pow(x, 2) + pow(y, 2));
}