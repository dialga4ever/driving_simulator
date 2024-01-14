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
        startRpm=500;
        power=100;
        gear=0;
        rpm=0;



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

    int Car::rpmToSpeed(){
        if(rpm<=500){
            return speed-(speed/10);
        }


        if(gear==0){
            return 0;
        }
        if(gear==1){
            return ((25)/(1+exp(-0.001*(rpm-3000))));
        }
        if(gear==2){
            return 10+((35)/(1+exp(-0.001*(rpm-3500))));
        }
        if(gear==3){
            return 25+((40)/(1+exp(-0.001*(rpm-3500))));
        }
        if(gear==-1){
            return -((25)/(1+exp(-0.001*(rpm-3000))));
        }
        return 0;
    }

    int Car::rpmToSpeed(int rpmToConvert, int gearToConvert){
        if(gearToConvert==0){
            return 0;
        }
        if(gearToConvert==1){
            return ((25)/(1+exp(-0.001*(rpmToConvert-3000))));
        }
        if(gearToConvert==2){
            return 10+((35)/(1+exp(-0.001*(rpmToConvert-3500))));
        }
        if(gearToConvert==3){
            return 25+((40)/(1+exp(-0.001*(rpmToConvert-3500))));
        }
        if(gearToConvert==-1){
            return -((25)/(1+exp(-0.001*(rpmToConvert-3000))));
        }
        return 0;
    }
    int Car::convertSpeedToRpm(int newGear){
        if (Keyboard::isKeyPressed(Keyboard::LShift)){
            return startRpm;
        }

        int last=0;
        for(int i=500;i<maxRpm;i=i+100){
            if(rpmToSpeed(i,newGear)>speed){
                printf("Curr : %d   rpmToSpeed :%d\n",i,rpmToSpeed(i,newGear));
                printf("Curr Speed : %f\n",speed);
                return last;
            }
            last=i;
        }
        printf("Last : %d   rpmToSpeed :%d\n",last,rpmToSpeed(last,newGear));

        return 0;
    }


    void Car::move(){

        if(started){
            if(Keyboard::isKeyPressed(Keyboard::LShift)){
                printf("a\n");
                if(Keyboard::isKeyPressed(Keyboard::Num0)){
                    printf("b\n");
                    gear=0;
                    rpm=500;
                }
                if(Keyboard::isKeyPressed(Keyboard::Num1)){
                    gear=1;
                    rpm=convertSpeedToRpm(1);
                    if(rpm=0){
                        started=false;
                        printf("Impossible de passer la vitesse tu a calé\n");
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Num2)){
                    gear=2;
                    rpm=convertSpeedToRpm(2);
                    if(rpm==0){
                        started=false;
                        printf("Impossible de passer la vitesse tu a calé\n");
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Num3)){
                    gear=3;
                    rpm=convertSpeedToRpm(3);
                    printf("rpm forReal%d\n",rpm);
                    if(rpm==0){
                        started=false;
                        printf("Impossible de passer la vitesse tu a calé\n");
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
                    gear=-1;
                    rpm=convertSpeedToRpm(-1);
                    if(rpm==0){
                        started=false;
                        printf("Impossible de passer la vitesse tu a calé\n");
                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)){
                if(gear==0||started){
                    
                    if(rpm<maxRpm){
                        rpm=rpm+100;
                    }
                    else{
                        rpm=maxRpm;
                    }
                }
            }
            else{
                if(rpm>500){
                    rpm=rpm-100;
                }
                else{
                    if(started){
                        rpm=500;
                    }
                    else{
                        rpm=rpm-100;
                        if(rpm<0){
                            rpm=0;
                        }
                    }
                    
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

            
            
            
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            reinisialisationCar(500,500);
        }
        if (Keyboard::isKeyPressed(Keyboard::E)){
            if(!isStarteting){
                isStarteting=true;
                if(started){
                    started=false;
                    rpm=0;
                }
                else{
                    started=true;
                    rpm=startRpm;
                }
            }
            
        }
        else{
            isStarteting=false;
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
        printf("started : %d\n",started);
        printf("speed : %f\n",speed);
        printf("rpm : %d\n",rpm);
        printf("vitesse : %d\n",gear);

        //if sift is pressed slow down the car
        if (Keyboard::isKeyPressed(Keyboard::LShift)){
            speed=speed/1.1;
        }
        else{
            speed=rpmToSpeed();
        }
        



        rectangle.move(cos(carDir * PI / 180.0)*speed/10.0, sin(carDir * PI / 180.0)*speed/10.0);
        wheel.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*40),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*40));

        wheel.setRotation(rectangle.getRotation()+wheelDir*2);
    }

    void Car::reinisialisationCar(int x, int y){
        rectangle.setPosition(x,y);
        rectangle.setRotation(0);
        wheel.setPosition(x-10,y+4);
        wheel.setRotation(rectangle.getRotation()+wheelDir);
    }
