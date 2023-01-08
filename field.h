#ifndef FIELD_H
#define FIELD_H

#include "line.h"
#include "ball.h"

#include <vector>
#include <iostream>

class Field {
private:
    Point bottom_left, bottom_right, top_right, top_left;
    vector<Point> input_points;

public:
    Field() : bottom_left(), bottom_right(), top_right(), top_left() {}
    Field(Point& bottom_left, double width, double height);
    Field(Point& bottom_left, Point& bottom_right, Point& top_right, Point& top_left);
    Field& operator=(const Field& other);

    void resize_field(const Ball& ball);
    bool is_point_in_bounds(const Point& point) const;
    bool is_ball_in_bounds(const Point& point) const;
    Line find_intersecting_line(Ball& ball, const Ball& destination);
    void hit_ball(Ball& ball);

    friend istream& operator>>(istream& is, Field& field);
    friend ostream& operator<<(ostream& os, const Field& field);
};

inline istream& operator>>(istream& is, Field& field) {
    for(Point& input_point : field.input_points) {
        is >> input_point;
    }

    return is;
}

inline ostream& operator<<(ostream& os, const Field& field) {
    os << "Field points:" << endl;
    for(const Point& input_point : field.input_points) {
        os << input_point;
    }

    return os;
}

#endif
