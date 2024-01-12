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
    int carDir;// In degrees
    float wheelDir;// In degrees
    int maxDir;
    int maxSpeed;
    bool actif;
    RectangleShape rectangle;

    // Constructor
    Car(int x_x, int y_y);


    void move();

    void deceleration();

    void deplacement();

    void reinisialisationCar(int, int);
};
