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
        carDir = 0;
        wheelDir =0;
        maxDir=8;
        maxSpeed=15;
        rectangle.setSize({30,20});
        rectangle.setOrigin(10,10);
        rectangle.setOutlineColor(Color::Blue);
        //rectangle.setOutlineThickness(10);
        rectangle.setPosition(x,y);
    }

    void Car::move(){

        printf("DIR  %f\n",wheelDir);
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            actif=true;
            if(abs(wheelDir)<maxDir||wheelDir>0){
                
                if(abs(speed) > 3){
                    wheelDir -= 0.1;
                }else{
                    wheelDir -= 0.2;
                }
            }
        }
        else{
            if (Keyboard::isKeyPressed(Keyboard::Right)){ 
                actif=true;
                if(abs(wheelDir)<maxDir||wheelDir<0){
                    if(abs(speed) > 3){
                        wheelDir += 0.1;
                    }else{
                        wheelDir += 0.2;
                    }
                }
            }
            else{
                //
            }
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
        if(actif){
            actif=false;
        }
        else{
            if(speed!=0){
                if(abs(wheelDir)<0.19){
                    wheelDir=0;
                }
                    else{
                        if(wheelDir>0){
                        wheelDir-=0.2;
                    }
                    else{
                        wheelDir+=0.2;
                    }
                }
            }
        }

        if(speed!=0){
            if(speed<0){
                rectangle.setRotation(carDir+(wheelDir/3));
                carDir=carDir+(wheelDir/3);
            }else{
                rectangle.setRotation(carDir+(wheelDir/2));
                carDir=carDir+(wheelDir/2);
            }
        }


        rectangle.move(cos(carDir * PI / 180.0)*speed, sin(carDir * PI / 180.0)*speed);
    }

    void Car::reinisialisationCar(int x, int y){
        rectangle.setPosition(x,y);
        rectangle.setRotation(0);
    }
