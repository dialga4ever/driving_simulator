#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

class Car{
    struct Phare{
        int x;
        int y;

        Sprite image;
    };

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
    struct Phare phares;
    RectangleShape rectangle;
    RectangleShape wheelLeft;
    RectangleShape wheelRight;
    Texture carTexture;
    Texture wheeltexture;

    // Constructor
    Car();
    Car(int x_x, int y_y, bool nocturne);
    Car(int x_x, int y_y, bool nocturne, map<string, Texture> *textures);

    int rpmToSpeed();
    int rpmToSpeed(int rpmToConvert, int gearToConvert);

    int convertSpeedToRpm(int newGear);

    void move();

    void deceleration();

    void deplacement(Car prev_car, vector<Sprite> *obstacles);

    void reinisialisationCar(int, int);

};


