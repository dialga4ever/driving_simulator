#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include "settings.h"

using namespace std;
using namespace sf;

class Car{

    public:
    Font font;
    bool started;
    bool isStarteting;
    bool embrayage;
    int x;
    int y;
    float defaultAngle;
    float speed;
    float carDir;// In degrees
    float wheelDir;// In degrees
    int maxDir;
    int maxSpeed;
    bool actif;
    int maxRpm;
    int startRpm;
    int rpm;
    int nb_point=500;
    int power;
    int gear;
    bool nocturne;
    bool boiteAuto=true;
    bool win = false;

    chrono::time_point<chrono::system_clock> start_time;
    float time = 0;
    bool game_started = false;

    Texture pharesTexture;
    RectangleShape phares;
    Sprite rectangle;
    RectangleShape wheelLeft;
    RectangleShape wheelRight;
    Texture carTexture;
    Texture wheeltexture;


    /*Texture fondCompteurTex;
    Sprite fondCompteur;*/
    Sprite compteur;
    Texture compteurTex;
    Texture aiguilleTex;
    Sprite aiguille1;
    Sprite aiguille2;
    Sprite boite;
    Texture boiteRM; 
    Texture boite0M;
    Texture boite1M;
    Texture boite2M;
    Texture boite3M;

    Texture boiteRA;
    Texture boite0A;
    Texture boiteDA;

    Texture fondCarInfoTex;
    Sprite fondCarInfo;
    Text carInfo;

    Keys* game_keys;
    // Constructor
    Car();
    Car(float defaultAngle_A,int x_x, int y_y, bool nocturne, Keys* game_keys, RenderWindow* window, Font font);

    int rpmToSpeed();
    int rpmToSpeed(int rpmToConvert, int gearToConvert);

    int convertSpeedToRpm(int newGear);

    void move();

    void deceleration();

    void deplacement( vector<Sprite> *obstacles, vector<Sprite> *places_parking);

    void reinisialisationCar();

};


