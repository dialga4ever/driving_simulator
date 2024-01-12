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
        started=false;
        maxRpm=7500;


        rectangle.setSize({60,40});
        rectangle.setOrigin(10,10);
        rectangle.setOutlineColor(Color::Blue);
        rectangle.setPosition(x,y);
        rectangle.setSize({60,40});
        wheel.setPosition(x+40,y);
        wheel.setSize({15,6});
        wheel.setFillColor(Color::Red);
        wheel.setOrigin(0,0);
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

        
        if(started){
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
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            reinisialisationCar(500,500);
        }
        if (Keyboard::isKeyPressed(Keyboard::E)){
            if(started){
                started=false;
            }
            else{
                started=true;
            }
        }
    }

    void Car::deceleration(){
        if(speed > 3){
            speed -= speed / 60;
        }else if(speed > 0){
            speed -= 0.1;
            if(speed < 0){
                speed = 0;
            }
        }else if(speed > -2){
            speed += 0.4;
            if(speed > 0){
                speed = 0;
            }
        }else{
            speed -= speed / 60;
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
                rectangle.setRotation(carDir+(-wheelDir/6));
                carDir=carDir+(-wheelDir/6);
            }else{
                rectangle.setRotation(carDir+(wheelDir/3));
                carDir=carDir+(wheelDir/3);
            }
        }


        rectangle.move(cos(carDir * PI / 180.0)*speed, sin(carDir * PI / 180.0)*speed);
        wheel.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*40),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*40));

        wheel.setRotation(rectangle.getRotation()+wheelDir*2);
    }

    void Car::reinisialisationCar(int x, int y){
        rectangle.setPosition(x,y);
        rectangle.setRotation(0);
        wheel.setPosition(x-10,y+4);
        wheel.setRotation(rectangle.getRotation()+wheelDir);
    }
