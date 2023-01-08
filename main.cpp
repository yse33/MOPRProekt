#include "field.h"
#include "ball.h"

void print_menu();
void print_information(Field& field, Ball& ball);
Field simple_field();
Field complex_field();
Field initialize_field();
Ball initialize_ball();

int main() {
    cout << "Please choose a format for initializing the field:" << endl;
    Field field = initialize_field();
    Ball ball = initialize_ball();

    field.resize_field(ball);


    while (true) {
        print_menu();

        int option = 0;
        cin >> option;

        switch (option) {
            case 1:
                cout << "Which method do you want to use for the new field:" << endl;
                field = initialize_field();
                field.resize_field(ball);
                ball = initialize_ball();
                break;

            case 2:
                if(ball.edit_ball() == 2) {
                    field.resize_field(ball);
                }
                break;

            case 3:
                field.hit_ball(ball);
                break;

            case 4:
                print_information(field, ball);
                break;

            case 5:
                break;

            default:
                cout << "Unknown command, please enter a number between 1 and 5" << endl;
        }

        if (5 == option) {
            return 0;
        }
    }
}

void print_menu() {
    cout << "Please enter the number of one of the following actions to execute it:" << endl;
    cout << "1. Edit field properties" << endl;
    cout << "2. Edit ball properties" << endl;
    cout << "3. Hit ball" << endl;
    cout << "4. Print information" << endl;
    cout << "5. Exit" << endl;
}

void print_information(Field& field, Ball& ball) {
    cout << field << ball;
}

Field simple_field() {
    cout << "Please enter the starting point, the height and the width of the field" << endl;

    Point bottom_left;
    cin >> bottom_left;

    double width = 0, height = 0;
    cin >> width >> height;

    return Field(bottom_left, width, height);
}

Field complex_field() {
    cout << "Please enter the coordinates of each point" << endl;

    Point bottom_left, bottom_right, top_right, top_left;

    cin >> bottom_left;
    cin >> bottom_right;
    cin >> top_right;
    cin >> top_left;

    return Field(bottom_left, bottom_right, top_right, top_left);
}

Field initialize_field() {
    cout << "1. Simple" << endl;
    cout << "2. Complex" << endl;

    int option = 0;
    cin >> option;

    switch (option) {
        case 1:
            return simple_field();

        case 2:
            return complex_field();

        default:
            return Field();
    }
}

Ball initialize_ball() {
    Ball ball;

    cout << "Enter starting coordinates for the ball and it's diameter" << endl;
    cin >> ball;

    return ball;
}