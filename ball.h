#ifndef BALL_H
#define BALL_H

#include "point.h"

#include <iostream>

class Ball {
private:
    double diameter;
    Point initial_position;
    Point current_position;

public:
    Ball() : diameter(0), initial_position(), current_position() {}
    Ball& operator=(const Ball& other);

    int edit_ball();
    void edit_ball_initial_position();

    friend class Field;
    friend istream& operator>>(istream& is, Ball& ball);
    friend ostream& operator<<(ostream& os, const Ball& ball);
};

inline istream& operator>>(istream& is, Ball& ball) {
    is >> ball.current_position >> ball.diameter;
    ball.initial_position = ball.current_position;
    return is;
}

inline ostream& operator<<(ostream& os, const Ball& ball) {
    os << "Ball center - " << ball.current_position;
    os << "Ball diameter - " << ball.diameter << endl;
    return os;
}

#endif
