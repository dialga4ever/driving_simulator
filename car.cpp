#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "car.h"

using namespace std;
using namespace sf;

#define PI 3.14159265


    Car::Car(int x_x, int y_y){
        x = x_x;
        y = y_y;
        speed = 0;
        dir = 0;

        rectangle.setSize({150,150});
        rectangle.setOrigin(75,75);
        rectangle.setOutlineColor(Color::Blue);
        rectangle.setOutlineThickness(10);
        rectangle.setPosition(x,y);
    }

    void Car::move(){
        if (Keyboard::isKeyPressed(Keyboard::Left)){
                dir += 3;
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)){ 
                dir -= 3;
            }

            if (Keyboard::isKeyPressed(Keyboard::Up)){ 
                speed += 0.5;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)){
                speed -= 0.5;
            }
            //d
    }

    void Car::deceleration(){
        if(speed > 3){
            speed -= speed / 30;
        }else if(speed > 0){
            speed -= 0.05;
            if(speed < 0){
                speed = 0;
            }
        }else if(speed > -3){
            speed += 0.05;
            if(speed > 0){
                speed = 0;
            }
        }else{
            speed -= speed / 30;
        }
    }

    void Car::deplacement(){
        rectangle.setRotation(dir);
        rectangle.move(cos(dir * PI / 180.0)*speed, sin(dir * PI / 180.0)*speed);
    }
