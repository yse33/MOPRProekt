#include "ball.h"

Ball& Ball::operator=(const Ball& other) {
    if (this != &other) {
        this->diameter = other.diameter;
        this->initial_position = other.initial_position;
        this->current_position = other.current_position;
    }

    return *this;
}

//printira menu, v koeto userut moje da izbere koq chast na topheto da editne
int Ball::edit_ball() {
    cout << "What do you want to change: " << endl;
    cout << "1. Ball's initial position" << endl;
    cout << "2. Ball's diameter" << endl;

    int option = 0;
    cin >> option;

    switch (option) {
        case 1:
            edit_ball_initial_position();
            break;
        case 2:
            cout << "Please enter new diameter: " << endl;
            cin >> diameter;
            break;
        default:
            cout << "Invalid input. Please enter a number(1-2)" << endl;
    }

    return option;
}

//pomoshtno menu, s koeto potrebitelqt moje da izbere kak da promeni nachalnata poziciq na topcheto
void Ball::edit_ball_initial_position() {
    cout << "Please pick a way to change the ball's initial position:" << endl;
    cout << "1. Enter new initial position" << endl;
    cout << "2. Use ball's current position as initial position" << endl;

    int option = 0;
    cin >> option;

    switch (option) {
        case 1:
            cout << "Enter new coordinates for the ball: " << endl;
            cin >> initial_position;
            cout << initial_position;
            break;
        case 2:
            initial_position = current_position;
            break;
        default:
            cout << "Invalid input. Please enter a number(1-2)" << endl;
    }

}
