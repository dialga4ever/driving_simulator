#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "car.h"
#include "collision.h"
#include <SFML/Graphics/Transformable.hpp>

using namespace std;
using namespace sf;

#define PI 3.14159265


Car::Car(){}

Car::Car(int x_x, int y_y, bool nocturne_, Keys* game_keys_, RenderWindow* window, Font font_){
    font = font_;
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
    phares.setSize({1000,1000});
    if(!pharesTexture.loadFromFile("src/other/phare.png")){
        std::cout << "Error: Couldn't load texture\n";
    }
    phares.setTexture(&pharesTexture);

    rectangle.setOrigin(0,0);
    rectangle.setPosition(x,y);
    rectangle.setOrigin({0,20});

    wheelLeft.setPosition(x-50,y);
    wheelLeft.setSize({15,6});
    wheelLeft.setFillColor(Color::Black);
    wheelLeft.setOrigin(7,3);

    wheelRight.setPosition(x+50,y);
    wheelRight.setSize({15,6});
    wheelRight.setFillColor(Color::Black);
    wheelRight.setOrigin(7,-9);
    game_keys = game_keys_;

    if (!carTexture.loadFromFile("src/other/voiture.png"))
    {
        std::cout << "Error: Couldn't load texture\n";
        
    }
    rectangle.setTexture(carTexture);

    compteurTex.loadFromFile("src/other/compteur.png");
    compteur.setTexture(compteurTex);
    compteur.setPosition(window->getSize().x-(compteurTex.getSize().x/2),window->getSize().y);
    compteur.setOrigin(compteurTex.getSize().x/2, compteurTex.getSize().y);


    aiguilleTex.loadFromFile("src/other/aiguille.png");
    aiguille1.setTexture(aiguilleTex);
    aiguille1.setScale(0.8,0.8);
    aiguille2.setTexture(aiguilleTex);
    aiguille2.setScale(1.5,1.5);
    aiguille1.setPosition(compteur.getPosition().x-compteurTex.getSize().x*0.243,compteur.getPosition().y-3);
    aiguille1.setOrigin(aiguilleTex.getSize().x*0.18, aiguilleTex.getSize().y/2);
    aiguille2.setPosition(compteur.getPosition().x+compteurTex.getSize().x*0.155,compteur.getPosition().y-10);
    aiguille2.setOrigin(aiguilleTex.getSize().x*0.18, aiguilleTex.getSize().y/2);

    carInfo.setFont(font); 
    carInfo.setString("Info");
    carInfo.setCharacterSize(24); 
    carInfo.setFillColor(Color::White);
    carInfo.setStyle(Text::Bold | Text::Underlined);
    carInfo.setPosition(0,0);
}



int Car::rpmToSpeed(){
    if(rpm<startRpm){
        if(!boiteAuto){
            started=false;
            return 0;
        }
        else{
            return 0;
        }

        
    }
    if(rpm>maxRpm+200){
        started=false;
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
            return last;
        }
        last=i;
    }

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
        if(Keyboard::isKeyPressed(game_keys->map_keys["Gear back 1"].keyCode)){
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
            if(Keyboard::isKeyPressed(game_keys->map_keys["Gear back 1"].keyCode)){
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
        if(!game_started){
            start_time = chrono::system_clock::now();
            game_started = true;
        }
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
            rectangle.setRotation(carDir+(wheelDir/maxDir*(speed/maxSpeed)));
            carDir=carDir+(wheelDir/maxDir*(speed/maxSpeed));
        }else if(speed>1){
            rectangle.setRotation(carDir+(wheelDir/maxDir*(speed/maxSpeed))/1.5);
            carDir=carDir+(wheelDir/maxDir*(speed/maxSpeed)/1.5);
        }
    }


    char s[256];
    float time = 0;
    if(game_started)
        time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count();
        time = time/1000;
    sprintf(s,"Started : %s\nSpeed : %f\nrpm : %d\nVitesse : %d\nTime : %.3f",((started == 1) ? "true" : "false"),speed,rpm,gear,time);
    
    carInfo.setString(s);

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
                if(speed>=-1){
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
                if(abs(float(newSpeed-speed))<3){
                    speed=newSpeed;
                }
                else{
                    rpm=convertSpeedToRpm(gear);
                    speed=rpmToSpeed();
                }
            }
        }
    }






    phares.setPosition(rectangle.getPosition());
    phares.setRotation(rectangle.getRotation()-90);
    bool isCollision = false;
    rectangle.move(cos(carDir * PI / 180.0)*speed/10.0, sin(carDir * PI / 180.0)*speed/10.0);
    for(auto i : *obstacles){
        //pixelPerfectTest
        if(collision::pixelPerfectTest(rectangle, i, 0)){
            isCollision = true;
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

    sf::Vector2f topLeft = rectangle.getTransform().transformPoint(sf::Vector2f(0, 0));
    sf::Vector2f topRight = rectangle.getTransform().transformPoint(sf::Vector2f(0, 0));
    sf::Vector2f bottomleft = rectangle.getTransform().transformPoint(sf::Vector2f(0, 0));
    sf::Vector2f bottomRight = rectangle.getTransform().transformPoint(sf::Vector2f(0, 0));


    wheelRight.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*90)-(sin(rectangle.getRotation()*PI/180)*13),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*90)+(cos(rectangle.getRotation() * PI / 180.0)*13));
    wheelRight.setRotation(rectangle.getRotation()+wheelDir*2);


    wheelLeft.setPosition(rectangle.getPosition().x+(cos(rectangle.getRotation() * PI / 180.0)*90)+(sin(rectangle.getRotation()*PI/180)*12),rectangle.getPosition().y+(sin(rectangle.getRotation() * PI / 180.0)*90)-(cos(rectangle.getRotation() * PI / 180.0)*12));
    wheelLeft.setRotation(rectangle.getRotation()+wheelDir*2);

    aiguille1.setRotation(170 + rpm*100/7500);
    aiguille2.setRotation(180 + abs(speed));
}

void Car::reinisialisationCar(int x, int y){
    rectangle.setPosition(x,y);
    rectangle.setRotation(0);
}



