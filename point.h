#ifndef POINT_H
#define POINT_H

#include <fstream>
#include <cmath>

using namespace std;

class Point {
private:
    double x, y;

public:
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    Point& operator=(const Point& other);
    Point& operator+(const Point& other);
    bool operator==(const Point& other);

    double distance_to_point(const Point& point) const;

    friend class Vector;
    friend class Line;
    friend class Field;
    friend class Ball;
    friend istream& operator>>(istream& is, Point& point);
    friend ostream& operator<<(ostream& os, const Point& point);
};

inline istream& operator>>(istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}

inline ostream& operator<<(ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")" << endl;
    return os;
}

#endif
