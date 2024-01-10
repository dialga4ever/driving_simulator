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
        maxDir=30;
        rectangle.setSize({100,100});
        rectangle.setOrigin(50,50);
        rectangle.setOutlineColor(Color::Blue);
        rectangle.setOutlineThickness(10);
        rectangle.setPosition(x,y);
    }

    void Car::move(){
        if (Keyboard::isKeyPressed(Keyboard::Left)){
                //if(dir<maxDir){
                    dir += 3;
                //}
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)){ 
                //if(dir>-maxDir){
                    dir -= 3;
                //}
            }

            if (Keyboard::isKeyPressed(Keyboard::Up)){ 

                if(speed < 5 || speed > 0){
                    speed += 2;
                }else{
                    speed += 1;  
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)){
                speed -= 2;
            }
            
    }

    void Car::deceleration(){
        if(speed > 3){
            speed -= speed / 10;
        }else if(speed > 0){
            speed -= 0.5;
            if(speed < 0){
                speed = 0;
            }
        }else if(speed > -3){
            speed += 0.5;
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
