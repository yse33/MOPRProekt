#ifndef LINE_H
#define LINE_H

#include "vector.h"

class Line {
private:
    double A, B, C;

public:
    Line() : A(0), B(0), C(0) {}
    Line(double A, double B, double C) : A(A), B(B), C(C) {}
    Line(const Point& p1, const Point& p2);
    Line(const Point& p, const Vector& v);

    Line& operator=(const Line& other);
    bool operator==(const Line& other) const;

    Point intersection(Line line) const;
    Point symmetrical(const Point& point) const;
    bool are_parallel(const Line& other) const;

    friend class Field;
    friend ostream& operator<<(ostream& os, const Line& line);
};

inline ostream& operator<<(ostream& os, const Line& line) {
    os << line.A << line.B << line.C << endl;
    return os;
}

#endif
