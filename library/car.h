#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

class Car{

    public:
    float started;
    int x;
    int y;
    float speed;
    int carDir;// In degrees
    float wheelDir;// In degrees
    int maxDir;
    int maxSpeed;
    bool actif;
    RectangleShape rectangle;
    RectangleShape wheel;

    // Constructor
    Car(int x_x, int y_y);


    void move();

    void deceleration();

    void deplacement();

    void reinisialisationCar(int, int);
};
