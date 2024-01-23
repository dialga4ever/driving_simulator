#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "car.h"

using namespace std;
using namespace sf;

#define PI 3.14159265


Car::Car(){}

Car::Car(int x_x, int y_y, bool nocturne_, Keys* game_keys_){
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

    nocturne = nocturne_;
    phares.setOrigin(x+15,y-200);
    phares.setPosition(x, y);
    printf("\nx %f  y %f\n\n\n", phares.getPosition().x, phares.getPosition().y);
    phares.setSize({1000,1000});
    if(!pharesTexture.loadFromFile("src/other/phare.png")){
        std::cout << "Error: Couldn't load texture\n";
    }
    phares.setTexture(&pharesTexture);

    rectangle.setOrigin(10,10);
    rectangle.setOutlineColor(Color::Blue);
    rectangle.setPosition(x,y);
    rectangle.setSize({75,40});
    rectangle.setOrigin({32,20});

    wheelLeft.setPosition(x+35,y);
    wheelLeft.setSize({15,6});
    wheelLeft.setFillColor(Color::Red);
    wheelLeft.setOrigin(7,6);

    wheelRight.setPosition(x+35,y);
    wheelRight.setSize({15,6});
    wheelRight.setFillColor(Color::Red);
    wheelRight.setOrigin(7,0);
    game_keys = game_keys_;

    if (!carTexture.loadFromFile("src/texture/car.png"))
    {
        std::cout << "Error: Couldn't load texture\n";
        
    }
    rectangle.setTexture(&carTexture);
}



int Car::rpmToSpeed(){
    if(rpm<startRpm){
        if(!boiteAuto){
            printf("Tu a calé\n");
            started=false;
            return 0;
        }
        else{
            return 0;
        }

        
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
    if(boiteAuto){
        if(Keyboard::isKeyPressed(game_keys->map_keys["Gear0"].keyCode)){
            gear=0;
            rpm=500;
        }
        if(Keyboard::isKeyPressed(game_keys->map_keys["Gear1"].keyCode)){
            if(speed>-2&&speed<26){
                gear=1;
            }
        }
        if(Keyboard::isKeyPressed(game_keys->map_keys["Gear_back_1"].keyCode)){
            if(speed<=1){
                gear=-1;
            }
        }
    }
    else{
        if(Keyboard::isKeyPressed(game_keys->map_keys["Clutch"].keyCode)){
            if(Keyboard::isKeyPressed(game_keys->map_keys["Gear0"].keyCode)){
                gear=0;
                rpm=500;
            }
            if(Keyboard::isKeyPressed(game_keys->map_keys["Gear1"].keyCode)){
                gear=1;
            }
            if(Keyboard::isKeyPressed(game_keys->map_keys["Gear2"].keyCode)){
                
                gear=2;
                
            }
            if(Keyboard::isKeyPressed(game_keys->map_keys["Gear3"].keyCode)){
                
                gear=3;
                
            }
            if(Keyboard::isKeyPressed(game_keys->map_keys["Gear_back_1"].keyCode)){
                gear=-1;
            }
        }
    }
    
    if(started){
        
        if (Keyboard::isKeyPressed(game_keys->map_keys["Up"].keyCode)){
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
                rpm=rpm-40;
            }
            else{
                if(started){
                    rpm=500;
                }
                else{
                    rpm=rpm-40;
                    if(rpm<0){
                        rpm=0;
                    }
                }
                
            }
        }
        if (Keyboard::isKeyPressed(game_keys->map_keys["Down"].keyCode)){
            if(!speed==0){
                if(speed>0){
                    speed=speed-(200/(speed*speed));
                }
                else{
                    printf("%f\n",speed);
                    printf("%f\n",(200/(-speed*-speed)));
                    speed=speed+(200/(-speed*-speed));
                    if(speed>0){
                        speed=0;
                    }
                }
                rpm=convertSpeedToRpm(gear);
            }
        }
        if (Keyboard::isKeyPressed(game_keys->map_keys["Left"].keyCode)){
            actif=true;
            if(abs(wheelDir)<maxDir||wheelDir>0){
                
                if(abs(speed) > 3){
                    wheelDir -= 0.2;
                }else{
                    wheelDir -= 0.3;
                }
            }
        }
        else{
            if (Keyboard::isKeyPressed(game_keys->map_keys["Right"].keyCode)){
                actif=true;
                if(abs(wheelDir)<maxDir||wheelDir<0){
                    if(abs(speed) > 3){
                        wheelDir += 0.2;
                    }else{
                        wheelDir += 0.3;
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
    if (Keyboard::isKeyPressed(game_keys->map_keys["Start"].keyCode)){
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

void Car::deplacement(Car prev_car, vector<Sprite> *obstacles){
    if(!actif){
        if(speed!=0){
            if(abs(wheelDir)<0.19){
                wheelDir=0;
            }
                else{
                    if(wheelDir>0){
                    wheelDir-=0.1;
                }
                else{
                    wheelDir+=0.1;
                }
            }
        }
        
    }
    actif=false;

    if(speed!=0){
        if(speed<0&&speed<-1&&speed>-27){
            printf("NAN MAIS WAZEFUKWA");
            rectangle.setRotation(carDir+(-wheelDir/maxDir*(speed/maxSpeed))*2);
            carDir=carDir+(-wheelDir/maxDir*(speed/maxSpeed));
        }else if(speed>1){
            rectangle.setRotation(carDir+(wheelDir/maxDir*(speed/maxSpeed)));
            carDir=carDir+(wheelDir/maxDir*(speed/maxSpeed));
        }
    }
    
    printf("started : %d\n",started);
    printf("speed : %f\n",speed);
    printf("rpm : %d\n",rpm);
    printf("vitesse : %d\n",gear);


    if(boiteAuto){
        if(gear>=1){
            if(rpm>=7400){
                if(gear<3){
                    rpm=convertSpeedToRpm(gear+1);
                    gear=gear+=1;
                }

            }
            else{
                if(rpm<=700){
                    if(gear>1){
                        rpm=convertSpeedToRpm(gear-1);
                        gear=gear-=1;
                    }
                    else{
                        
                    }
                }
            }
        }
        speed=rpmToSpeed();
        if(speed<=1){
            if(gear==-1){
                if(speed>-1){
                    speed=0;
                }
            }
            else{
                speed=0;
            }
            
        }
    }
    else{
        if (Keyboard::isKeyPressed(game_keys->map_keys["Clutch"].keyCode)){
            embrayage=true;
        }
        if(embrayage){
            int tempRpm=convertSpeedToRpm(gear);
            if(tempRpm+200<rpm){
                rpm=tempRpm+500;
            }
            else{
                if(tempRpm-200>rpm){
                    rpm=tempRpm-500;
                }
            }
            embrayage=false;
            speed=speed-0.1;
            if(speed<0.5){
                speed=0;
            }
        }
        else{
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
    }


    



    phares.setPosition(rectangle.getPosition());
    phares.setRotation(rectangle.getRotation()-90);
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

    wheelRight.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*30)-(sin(rectangle.getRotation()*PI/180)*13),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*30)+(cos(rectangle.getRotation() * PI / 180.0)*13));
    wheelRight.setRotation(rectangle.getRotation()+wheelDir*2);


    wheelLeft.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*30)+(sin(rectangle.getRotation()*PI/180)*12),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*30)-(cos(rectangle.getRotation() * PI / 180.0)*12));
    wheelLeft.setRotation(rectangle.getRotation()+wheelDir*2);

    }

void Car::reinisialisationCar(int x, int y){
    rectangle.setPosition(x,y);
    rectangle.setRotation(0);
}



