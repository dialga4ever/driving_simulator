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
    int maxDir;
    RectangleShape rectangle;

    // Constructor
    Car();
    Car(int x_x, int y_y);


    void move();

    void deceleration();

    void deplacement(vector<Sprite> *obstacles, Car image);

    void reinisialisationCar(int, int);

    bool collision(vector<Sprite> *obstacles);

    void stop(int old_x, int old_y, int old_dir);

    void copyCar(Car car);
};
