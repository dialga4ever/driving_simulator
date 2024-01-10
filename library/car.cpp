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
        rectangle.setSize({30,20});
        rectangle.setOrigin(15,10);
        rectangle.setOutlineColor(Color::Blue);
        //rectangle.setOutlineThickness(10);
        rectangle.setPosition(x,y);
    }

    void Car::move(){
        if (Keyboard::isKeyPressed(Keyboard::Left)){
                //if(dir<maxDir){
                if(speed != 0){
                    if(speed > 3){
                        dir -= 5;
                    }else if(speed > 0){
                        dir -= 3;
                    }else if(speed > -1.5){
                        dir += 2;
                    }else{
                        dir += 5;
                    }
                }
                //}
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)){ 
                //if(dir>-maxDir){
                if(speed != 0){
                    if(speed > 3){
                        dir += 5;
                    }else if(speed > 0){
                        dir += 3;
                    }else if(speed > -1.5){
                        dir -= 2;
                    }else{
                        dir -= 5;
                    }
                }
                //}
            }

            if (Keyboard::isKeyPressed(Keyboard::Up)){ 
                if(speed < 0){
                    speed += 1.5;
                }else if(speed < 5){
                    speed += 0.8;
                }else{
                    speed += 0.4;  
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)){
                if(speed > 0.5){
                    speed -= 2;
                }else if(speed > -1){
                    speed -= 1;
                }else{
                    speed -= 0.4;
                }
                
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)){
                reinisialisationCar(500,500);
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
        }else if(speed > -2){
            speed += 0.4;
            if(speed > 0){
                speed = 0;
            }
        }else{
            speed -= speed / 10;
        }
    }

    void Car::deplacement(){
        rectangle.setRotation(dir);
        rectangle.move(cos(dir * PI / 180.0)*speed, sin(dir * PI / 180.0)*speed);
    }

    void Car::reinisialisationCar(int x, int y){
        rectangle.setPosition(x,y);
        rectangle.setRotation(0);
    }
