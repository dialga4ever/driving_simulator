#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

class Car{

    public:

    int x;
    int y;
    float speed;
    int dir;// In degrees
    RectangleShape rectangle;

    // Constructor
    Car(int x_x, int y_y);


    void move();

    void deceleration();

    void deplacement();
};
