#include "line.h"

Line::Line(const Point& p1, const Point& p2) {
    A = p2.y - p1.y;
    B = p1.x - p2.x;
    C = p2.x * p1.y - p1.x * p2.y;
}

Line::Line(const Point& p, const Vector& v) {
    A = v.y;
    B = -v.x;
    C = v.x * p.y - v.y * p.x;
}

Line& Line::operator=(const Line& other) {
    if (this != &other) {
        this->A = other.A;
        this->B = other.B;
        this->C = other.C;
    }

    return *this;
}

bool Line::operator==(const Line& other) const {
    return this->A == other.A && this->B == other.B && this->C == other.C;
}

//namira tochkata v koqto se presichat dvete pravi
Point Line::intersection(Line line) const {
    double denominator = this->A * line.B - line.A * this->B;
    return Point((this->B * line.C - line.B * this->C) / denominator, (line.A * this->C - this->A * line.C) / denominator);
}

//vrushta tochka, simetrichna na podadenata, sprqmo pravata
Point Line::symmetrical(const Point& point) const {
    double denominator = A * A + B * B;
    double x = ((B * B * point.x) - (A * A * point.x) - (2 * A * B * point.y) - (2 * A * C)) / denominator;
    double y = ((A * A * point.y) - (B * B * point.y) - (2 * A * B * point.x) - (2 * B * C)) / denominator;
    return Point(x, y);
}

//proverqva dali 2 pravi sa usporedni edna na druga
bool Line::are_parallel(const Line& other) const {
    Vector v1 = Vector(this->B, -this->A);
    Vector v2 = Vector(other.B, -other.A);

    return v1.is_colinear(v2);
}