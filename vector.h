#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

class Vector {
private:
    double x, y;

public:
    Vector() : x(0), y(0) {}
    Vector(double x, double y) : x(x), y(y) {}
    Vector(const Point& p1, const Point& p2);

    void times_num(double num);
    double dot_product(const Vector& other) const;
    bool is_colinear(const Vector& other) const;
    double length() const;

    friend class Line;
    friend class Field;
    friend ostream& operator<<(ostream& os, const Vector& v);
};

inline ostream& operator<<(ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ")" << endl;
    return os;
}

#endif
