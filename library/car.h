#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "settings.h"

using namespace std;
using namespace sf;

class Car{

    public:
    bool started;
    bool isStarteting;
    bool embrayage;
    int x;
    int y;
    float speed;
    int carDir;// In degrees
    float wheelDir;// In degrees
    int maxDir;
    int maxSpeed;
    bool actif;
    int maxRpm;
    int startRpm;
    int rpm;
    int power;
    int gear;
    bool nocturne;
    Texture pharesTexture;
    RectangleShape phares;
    RectangleShape rectangle;
    RectangleShape wheelLeft;
    RectangleShape wheelRight;
    Texture carTexture;
    Texture wheeltexture;

    Keys* game_keys;
    // Constructor
    Car();
    Car(int x_x, int y_y, bool nocturne, Keys* game_keys);

    int rpmToSpeed();
    int rpmToSpeed(int rpmToConvert, int gearToConvert);

    int convertSpeedToRpm(int newGear);

    void move();

    void deceleration();

    void deplacement(Car prev_car, vector<Sprite> *obstacles);

    void reinisialisationCar(int, int);

};


