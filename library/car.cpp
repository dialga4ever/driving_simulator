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
        rectangle.setOutlineColor(Color::Blue);rectangle.setOutlineThickness(5);
        rectangle.setPosition(x,y);
        rectangle.setSize({75,40});
        wheelLeft.setPosition(x+35,y);
        wheelLeft.setSize({15,6});
        wheelLeft.setFillColor(Color::Red);
        wheelLeft.setOrigin(7,0);
        wheelRight.setPosition(x+35,y);
        wheelRight.setSize({15,6});
        wheelRight.setFillColor(Color::Red);
        wheelRight.setOrigin(7,0);


        if (!carTexture.loadFromFile("src/texture/car.png"))
        {
            std::cout << "Error: Couldn't load texture\n";
            
        }
        rectangle.setTexture(&carTexture);
    }

    int Car::rpmToSpeed(){
        if(rpm<startRpm){
            printf("Tu a calé\n");
            started=false;
            return 0;
        }
        if(rpm>maxRpm+200){
            started=false;
            printf("Tu a calé\n");
            return 0;
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
        //if (Keyboard::isKeyPressed(Keyboard::LShift)){
        //    return startRpm;
        //}

        int last=0;
        for(int i=500;i<maxRpm;i=i+100){
            if(rpmToSpeed(i,newGear)>speed){
                printf("Curr : %d   rpmToSpeed :%d\n",i,rpmToSpeed(i,newGear));
                printf("Curr Speed : %f\n",speed);
                printf("Last: %d\n",last);
                return last;
            }
            last=i;
        }
        printf("Last : %d   rpmToSpeed :%d\n",last,rpmToSpeed(last,newGear));

        return 0;
    }


    void Car::move(){
        if(Keyboard::isKeyPressed(Keyboard::LShift)){
            printf("a\n");
            if(Keyboard::isKeyPressed(Keyboard::Num0)){
                printf("b\n");
                gear=0;
                rpm=500;
            }
            if(Keyboard::isKeyPressed(Keyboard::Num1)){
                gear=1;
                //rpm=convertSpeedToRpm(1);
                //if(rpm=0){
                //    printf("cA\n");
                //    started=false;
                //    printf("Impossible de passer la vitesse tu a calé\n");
                //}
            }
            if(Keyboard::isKeyPressed(Keyboard::Num2)){
                gear=2;
                //rpm=convertSpeedToRpm(2);
                //if(rpm==0){
                //    printf("cB\n");
                //    started=false;
                //    printf("Impossible de passer la vitesse tu a calé\n");
                //}
            }
            if(Keyboard::isKeyPressed(Keyboard::Num3)){
                gear=3;
                //rpm=convertSpeedToRpm(3);
                //printf("rpm forReal%d\n",rpm);
                //if(rpm==0){
                //                            printf("cC\n");
                //    started=false;
                //    printf("Impossible de passer la vitesse tu a calé\n");
                //}
            }
            if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
                gear=-1;
                //rpm=convertSpeedToRpm(-1);
                //if(rpm==0){                        printf("cD\n");

                //    started=false;
                //    printf("Impossible de passer la vitesse tu a calé\n");
                //}
            }
        }
        if(started){
            
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
                    rpm=rpm-10;
                }
                else{
                    if(started){
                        rpm=500;
                    }
                    else{
                        rpm=rpm-10;
                        if(rpm<0){
                            rpm=0;
                        }
                    }
                    
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)){
                if(!speed==0){
                    if(speed>0){
                    speed=speed-(200/(speed*speed));
                    if(speed<0){
                        speed=0;
                    }
                    }
                    else{
                        speed=speed+(200/(-speed*-speed));
                        if(speed>0){
                            speed=0;
                        }
                    }
                    rpm=convertSpeedToRpm(gear);
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
                                            printf("cE\n");

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

    void Car::deplacement(Car prev_car, vector<Sprite> *obstacles){
        if(!actif){
            printf("AAA\n");
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
        actif=false;

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
            embrayage=true;
        }
        else{
            if(embrayage){
                int tempRpm=convertSpeedToRpm(gear);
                //print all info
                printf("rpm : %d\n",rpm);
                printf("tempRpm : %d\n",tempRpm);
                printf("speed : %f\n",speed);


                if(tempRpm+200<rpm){
                    rpm=tempRpm+500;
                }
                else{
                    if(tempRpm-200>rpm){
                        rpm=tempRpm-500;
                    }
                }
                embrayage=false;
            }
            int newSpeed=rpmToSpeed();
            if(newSpeed==0){
                speed=speed/1.1;
                if(speed<0.5){
                    speed=0;
                }
            }
            else{
                printf("newSpeed : %d\n",newSpeed);
                printf("newSpeed : %f\n",speed);
                if(abs(float(newSpeed-speed))<3){
                    speed=newSpeed;
                }
                else{
                    rpm=convertSpeedToRpm(gear);
                    speed=rpmToSpeed();
                    printf("Maybe tu cale\n\n\n\n");
                }
                
            }
        }
        


        bool isCollision = false;
        rectangle.move(cos(carDir * PI / 180.0)*speed/10.0, sin(carDir * PI / 180.0)*speed/10.0);
        for(auto i : *obstacles){
            if( rectangle.getGlobalBounds().intersects(i.getGlobalBounds())){
                isCollision = true;
                i.scale({2.0,2.0});
            }
        }
        if(isCollision){
            *this = prev_car;
            speed = 0;
            rpm = 0;
            started = false;
        }else{
            prev_car= *this;
        }

        wheelRight.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*45)-(sin(rectangle.getRotation()*PI/180)*25),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*45)+(cos(rectangle.getRotation() * PI / 180.0)*25));
        wheelRight.setRotation(rectangle.getRotation()+wheelDir*2);


        wheelLeft.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*45)+(sin(rectangle.getRotation()*PI/180)*10),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*45)-(cos(rectangle.getRotation() * PI / 180.0)*10));
        wheelLeft.setRotation(rectangle.getRotation()+wheelDir*2);
    }

    void Car::reinisialisationCar(int x, int y){
        rectangle.setPosition(x,y);
        rectangle.setRotation(0);
    }



