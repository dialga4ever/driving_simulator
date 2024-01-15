#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "car.h"

using namespace std;
using namespace sf;

#define PI 3.14159265
Car::Car(){}

Car::Car(int x_x, int y_y){
    x = x_x;
    y = y_y;
    speed = 0;
    dir = 0;
    maxDir=30;
    rectangle.setSize({30,20});
    rectangle.setOrigin(10,10);
    rectangle.setOutlineColor(Color::Blue);
    rectangle.setPosition(x,y);
}

void Car::move(){
    if (Keyboard::isKeyPressed(Keyboard::Left)){
        if(speed != 0){
            if(speed > 3){
                dir -= 5;
            }else if(speed > 0){
                dir -= 3;
            }else if(speed > -1.5){
                dir += 2;
            }else{
                dir += 3;
            }
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)){ 
        if(speed != 0){
            if(speed > 3){
                dir += 5;
            }else if(speed > 0){
                dir += 3;
            }else if(speed > -1.5){
                dir -= 2;
            }else{
                dir -= 3;
            }
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

void Car::deplacement(vector<Sprite> *obstacles, Car prev_car){
    
    if(collision(obstacles)){
        copyCar(prev_car);
        speed = 0;
    }else{
        
        
        prev_car.copyCar(*this);
    }
}

void Car::reinisialisationCar(int x, int y){
    rectangle.setPosition(x,y);
    rectangle.setRotation(0);
}

bool Car::collision(vector<Sprite> *obstacles){
    rectangle.setRotation(dir);
    rectangle.move(cos(dir * PI / 180.0)*speed, sin(dir * PI / 180.0)*speed);
    
    for(auto i : *obstacles){
        if( rectangle.getGlobalBounds().intersects(i.getGlobalBounds())){
            return true;
        }
    }
    return false;
}


void Car::stop(int old_x, int old_y, int old_dir){
    if(speed > 0){
        speed = -1;
    }else{
        speed = 1;
    }
    
    rectangle.setPosition(old_x, old_y);
    rectangle.setRotation(old_dir);
}

void Car::copyCar(Car car){
    x = car.rectangle.getPosition().x;
    y = car.rectangle.getPosition().y;
    speed = car.speed;
    dir = car.dir;
    maxDir=30;
    rectangle.setSize(car.rectangle.getSize());
    rectangle.setOrigin(car.rectangle.getOrigin());
    rectangle.setOutlineColor(car.rectangle.getOutlineColor());
    rectangle.setPosition(car.rectangle.getPosition());
    rectangle.setRotation(car.rectangle.getRotation());
}