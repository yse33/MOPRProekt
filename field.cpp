#include "field.h"

Field::Field(Point& bottom_left, double width, double height) {
    //proverka za dimenciite na poleto
    if (height != width / 2) {
        cout << "Height is " << height << " and width is " << width << endl;
        return;
    }

    this->bottom_left = bottom_left;
    bottom_right = Point(bottom_left.x + width, bottom_left.y);
    top_right = Point(bottom_right.x, bottom_right.y + height);
    top_left = Point(bottom_left.x, top_right.y);

    //tova e nujno, v sluchai che userut reshi da smeni koordinatite na poleto, a v tozi vector sa zapazeni starite
    input_points.clear();
}

Field::Field(Point& bottom_left, Point& bottom_right, Point& top_right, Point& top_left) {
    //proverka za dimenciite na poleto
    if (bottom_left.distance_to_point(bottom_right) != 2 * bottom_left.distance_to_point(top_left)) {
        cout << "Error because first distance is: " << bottom_left.distance_to_point(bottom_right)
             << " and second distance is: " << bottom_left.distance_to_point(top_left) << endl;
        return;
    }

    this->bottom_left = bottom_left;
    this->bottom_right = bottom_right;
    this->top_right = top_right;
    this->top_left = top_left;

    //veche obqsneno
    input_points.clear();
}

Field& Field::operator=(const Field& other) {
    if (this != &other) {
        this->bottom_left = other.bottom_left;
        this->bottom_right = other.bottom_right;
        this->top_right = other.top_right;
        this->top_left = other.top_left;
        this->input_points = other.input_points;
    }

    return *this;
}

//funkciq sa preorazmerqvane na poleto
//nujno e ako topcheto ima diametur, razlichen ot 0
//togava tochkite se dvijat po uglopolovqshtite si sprqmo radiusa na topcheto
void Field::resize_field(const Ball& ball) {
    //input_points e masiv, v koito az zapazvam purvonachalno zadadenite tochki ot potrebitelq
    //te shte budat izpolzvani samo za printvane na informaciq, kato 4-te pointa shte uchastvat vuv vsichki ostanali metodi
    if (!input_points.empty()) {
        //ako se vleze tuk, znachi, che veche sme smenqli razmerite na poleto, toest go pravim za vtori put.
        //zatova "restartirame" poziciite na tochkite, taka che da moje da gi mestim otnachalo,
        // veche imaiki predvid razlichen radius
        bottom_left = input_points.at(0);
        bottom_right = input_points.at(1);
        top_right = input_points.at(2);
        top_left = input_points.at(3);
        input_points.clear();
    }

    input_points.emplace_back(bottom_left);
    input_points.emplace_back(bottom_right);
    input_points.emplace_back(top_right);
    input_points.emplace_back(top_left);

    if (ball.diameter == 0) {
        return;
    }
    //namirame sredite na dvete dulgi strani na poleto
    Point AB_middle((bottom_right.x + bottom_left.x) / 2,
                    (bottom_right.y + bottom_left.y) / 2);
    Point CD_middle((top_right.x + top_left.x) / 2,
                    (top_right.y + top_left.y) / 2);

    //namriame chetirite uglopolovqshti na poleto kato go razdelim na dva kvadrata(blagodarenie na suotnoshenieto 2:1)
    vector<Vector> bisectors;
    bisectors.emplace_back(bottom_left, CD_middle);
    bisectors.emplace_back(bottom_right, CD_middle);
    bisectors.emplace_back(top_right, AB_middle);
    bisectors.emplace_back(top_left, AB_middle);

    //namirame raztoqnieto, koeto trqbva da izmine vsqka edna ot tochkite po posoka ulgopolovqshtata si
    for (auto & bisector : bisectors) {
        bisector.times_num(sqrt(2) * ball.diameter / (2 *  bisector.length()));
    }

    //mestim samite tochki, kato gi subirame s vectora, koito poluchihme po-gore
    bottom_left = bottom_left + Point(bisectors.at(0).x, bisectors.at(0).y);
    bottom_right = bottom_right + Point(bisectors.at(1).x, bisectors.at(1).y);
    top_right = top_right + Point(bisectors.at(2).x, bisectors.at(2).y);
    top_left = top_left + Point(bisectors.at(3).x, bisectors.at(3).y);
}

bool Field::is_point_in_bounds(const Point& point) const {
    //vektori za chetirite strani na pravougulnika
    Vector AB(bottom_left, bottom_right);
    Vector CB(top_right, bottom_right);
    Vector CD(top_right, top_left);
    Vector AD(bottom_left, top_left);
    //2 pomoshtni vektora - za vektorite ot A/C do segashnata poziciq na topcheto(T)
    Vector AT(bottom_left, point);
    Vector CT(top_right, point);

    //chrez skalarnoto proizvedenie proverqvame dali tochkata e mejdu stenite na poleto
    //tazi funkciq broi tochka, lejashta na enda ot pravite, no mejdu drugi 2, kato "in_bounds"
    //tova shte pomogne s namiraneto na tochkata, ot koqto se e rikoshiralo topcheto
    if (AT.dot_product(AB) >= 0 && AT.dot_product(AD) >= 0 &&
        CT.dot_product(CB) >= 0 && CT.dot_product(CD) >= 0) {
        return true;
    }

    return false;
}

bool Field::is_ball_in_bounds(const Point &point) const {
    //vektori za chetirite strani na pravougulnika
    Vector AB(bottom_left, bottom_right);
    Vector CB(top_right, bottom_right);
    Vector CD(top_right, top_left);
    Vector AD(bottom_left, top_left);
    //2 pomoshtni vektora - za vektorite ot A/C do segashnata poziciq na topcheto(T)
    Vector AT(bottom_left, point);
    Vector CT(top_right, point);

    //sushtoto, razlikata biva samo, che veche ako topcheto leji vurhy edna ot stenite, se broi, che ne e "in_bounds"
    if (AT.dot_product(AB) > 0 && AT.dot_product(AD) > 0 &&
        CT.dot_product(CB) > 0 && CT.dot_product(CD) > 0) {
        return true;
    }

    return false;
}

Line Field::find_intersecting_line(Ball& ball, const Ball& destination) {
    vector<Line> lines;
    vector<Point> intersection_points;
    //pravim si 5 linii - 4 za stenite i 1 za path-a na topcheto
    lines.emplace_back(bottom_left, bottom_right);
    lines.emplace_back(bottom_right, top_right);
    lines.emplace_back(top_right, top_left);
    lines.emplace_back(top_left, bottom_left);
    lines.emplace_back(ball.current_position, destination.current_position);

    //chrez tozi for dobavqme vsichki tochki, v koito se presichat suotvetnata strana i path-a na topcheto
    //if-ut vutre sluji, za da ne se vika funkciqta intersect() s paralelna na pravata prava,
    //zashtoto tova vodi do greshka
    for (int i = 0; i < 4; i++) {
        if (!lines.at(4).are_parallel(lines.at(i))) {
            intersection_points.push_back(lines.at(4).intersection(lines.at(i)));
        }
    }
    //tuk proverqvame dali topcheto e vlqzlo v nqkoq ot dupkite
    //ako ima poveche ot 2 intersection point-a, toest izstrelut ne e bil paralelen na nqkoi ot stenite
    //i ednovremenno s tova nqkoi intersection pointove suvpadat edni s drugi
    //to topcheto e vlqzlo v pocket
    if(intersection_points.size() > 2 && (intersection_points.at(0) == intersection_points.at(1)
       || intersection_points.at(0) == intersection_points.at(3))) {
        //poneje znam, che sum vlqzul v pocket, vrushtam topcheto v nachalnata my poziciq
        ball.current_position = ball.initial_position;
        cout << "Ball went into pocket" << endl;
        //vrushtam NaN, zashtoto dolu proverqvam dali A e NaN, i ako e - znam, che sum vlqzul v pocket
        return {NAN, NAN, NAN};
    }

    double distance = 0;
    //shte zapazim indexa na liniqta, ot koqto e rikoshiralo topcheto
    int index = 0;

    //tozi for vurti prez vsichki presechni tochki, kato tuk polezna e funckiqta is_POINT_in_bounds
    //tq shte vurne che TOCHNO 2 tockhi sa in_bounds i te shte sa na protivopolojni strani
    //sled kato namerim, che tochka e in_bounds, imame 3 varianta:
    //1) za pruv put vlizame tuk, toest pravim distance(pomoshtna promenliva) raven na distanciqta ot destinaciqta na topkata
    //do samata presechna tochka.(koqto distanciq e po-malka, ottam sme izlezli)
    //2) i 3) distance veche ima stoinost, toest sme proverili za protivopolojnata liniq
    //pri koqto ot dvete distanciqta e po-kusa, ottam sme izlezli ot poleto
    //kogato namerim v koq stena sme se blusnali, promenqme segashnata poziciq na topcheto na presechnata tochka
    //za da moje ako pak se udari, da imame adekvaten path
    for (int i = 0 ; i < intersection_points.size(); i++) {
        if (is_point_in_bounds(intersection_points.at(i))) {
            if (distance == 0) {
                index = i;
                distance = destination.current_position.distance_to_point(intersection_points.at(i));
            }
            else if (distance > destination.current_position.distance_to_point(intersection_points.at(i))){
                cout << "Ball bounced at" << intersection_points.at(i);
                ball.current_position = intersection_points.at(i);
                return lines.at(i);
            }
            else {
                cout << "Ball bounced at" << intersection_points.at(index);
                ball.current_position = intersection_points.at(index);
                return lines.at(index);
            }
        }
    }

    return {};
}

void Field::hit_ball(Ball& ball) {
    //suzdavame si temp_ball, chiqto current_position shte e tam, kudeto shte otide topcheto, ako ne se blusne v nishto
    //note: samoto ball ne se murda do vikane na find_intersection_line
    Ball temp_ball = ball;
    Point direction_point;
    float force = 0;

    cout << "Enter direction point coordinates:" << endl;
    cin >> direction_point;

    while (force < 1 || force > 10) {
        cout << "Enter ball force(float between 1-10): " << endl;
        cin >> force;
    }

    temp_ball.current_position.x =
            temp_ball.current_position.x - ((temp_ball.current_position.x - direction_point.x) * force);
    temp_ball.current_position.y =
            temp_ball.current_position.y - ((temp_ball.current_position.y - direction_point.y) * force);

    //dokato temp_ball(tam, kudeto trqbva da e topcheto) ne e v obsega na poleto, vurtim cikul, v koito:
    //namirame pravata ot koqto sme se otblusnali, pravim simetrichna na temp_ball.current_position tochka i smenqme
    //koordinatite na temp_ball tam
    //ako se schupi while-ut sled koeto, znachi nai-nakraq sme vutre, i smenqme segashnata poziciq na topcheto na tazi na temp_ball
    //tuk se namira if-ut, chrez koito namiram dali topcheto e vlqzlo v dupka
    //returnvam, za da ne se izpulni 238 red, poneje veche sme vurnali topcheto tam, kudeto trqbva da e
    while (!is_ball_in_bounds(temp_ball.current_position)) {
        Line intersection_line = find_intersecting_line(ball, temp_ball);
        if(isnan(intersection_line.A)){
            return;
        }
        temp_ball.current_position = intersection_line.symmetrical(temp_ball.current_position);
    }

    ball.current_position = temp_ball.current_position;
}

