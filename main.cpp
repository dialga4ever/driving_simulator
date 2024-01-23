#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "library/car.h"
#include "library/textureUtility.h"
#include "library/levelLoader.h"

using namespace std;
using namespace sf;

#define PI 3.14159265

bool IsSpriteCliked(Sprite tarket,RenderWindow *window){
    return tarket.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
}
void updateCursorSprite(Sprite *tarket,RenderWindow *window){
    tarket->setPosition(static_cast<Vector2f>(Mouse::getPosition(*window)));
}





int main()
{
    RenderWindow window(VideoMode(1024, 1024), "Driving Simulator", Style::Titlebar | Style::Close );
    window.setVerticalSyncEnabled(true);

    int fenetre = 0;




    Font font;
    if (!font.loadFromFile("src/font/arial.ttf"))
    {
        printf("pas de font");
    }



    Keys game_keys = Keys(&window, font);
    string change_key = "null";
    
    Car car(500, 500, false, &game_keys);// Création de la voiture

    Sprite compteur;
    Texture compteurTex;
    compteurTex.loadFromFile("src/other/compteur.png");
    compteur.setTexture(compteurTex);
    compteur.setPosition(window.getSize().x-(compteurTex.getSize().x/2),window.getSize().y);
    compteur.setOrigin(compteurTex.getSize().x/2, compteurTex.getSize().y);


    Texture aiguilleTex;
    aiguilleTex.loadFromFile("src/other/aiguille.png");
    Sprite aiguille1;
    Sprite aiguille2;
    aiguille1.setTexture(aiguilleTex);
    aiguille1.setScale(0.8,0.8);
    aiguille2.setTexture(aiguilleTex);
    aiguille2.setScale(1.5,1.5);
    aiguille1.setPosition(compteur.getPosition().x-compteurTex.getSize().x*0.243,compteur.getPosition().y-3);
    aiguille1.setOrigin(aiguilleTex.getSize().x*0.18, aiguilleTex.getSize().y/2);
    aiguille2.setPosition(compteur.getPosition().x+compteurTex.getSize().x*0.155,compteur.getPosition().y-10);
    aiguille2.setOrigin(aiguilleTex.getSize().x*0.18, aiguilleTex.getSize().y/2);


    Text carInfo;
    carInfo.setFont(font); 
    carInfo.setString("Info");
    carInfo.setCharacterSize(24); 
    carInfo.setFillColor(Color::White);
    carInfo.setStyle(Text::Bold | Text::Underlined);
    carInfo.setPosition(0,0);



//  ------MENU------  //



    Sprite play;
    Texture boutonTexture;
    centerOrigin(&play);
    spriteLoadFromFilePos(&play,&boutonTexture,"./src/other/test.jpg",window.getSize().y/2,200);
    play.scale({1,0.5});
    centerOrigin(&play);
    Text playText;
    playText.setFont(font); 
    playText.setString("Play");
    playText.setCharacterSize(24); 
    playText.setFillColor(Color::Black);
    playText.setStyle(Text::Bold | Text::Underlined);
    playText.setPosition(play.getPosition());
    centerTextOrigin(&playText);

    Sprite levelCreator;
    spriteLoadFromFilePos(&levelCreator,&boutonTexture,"./src/other/test.jpg",window.getSize().y/2,350);
    levelCreator.scale({1,0.5});
    centerOrigin(&levelCreator);
    Text levelCreatorText;
    levelCreatorText.setFont(font); 
    levelCreatorText.setString("Level Creator");
    levelCreatorText.setCharacterSize(24); 
    levelCreatorText.setFillColor(Color::Black);
    levelCreatorText.setStyle(Text::Bold | Text::Underlined);
    levelCreatorText.setPosition(levelCreator.getPosition());
    centerTextOrigin(&levelCreatorText);

    Sprite upgrade;
    spriteLoadFromFilePos(&upgrade,&boutonTexture,"./src/other/test.jpg",window.getSize().y/2,500);
    upgrade.scale({1,0.5});
    centerOrigin(&upgrade);
    upgrade.setColor(Color(255, 255, 255, 100));
    Text upgradeText;
    upgradeText.setFont(font); 
    upgradeText.setString("Upgrade car");
    upgradeText.setCharacterSize(24); 
    upgradeText.setFillColor(Color::Black);
    upgradeText.setStyle(Text::Bold | Text::Underlined);
    upgradeText.setPosition(upgrade.getPosition());
    centerTextOrigin(&upgradeText);
    
    Sprite settings;
    spriteLoadFromFilePos(&settings,&boutonTexture,"./src/other/test.jpg",window.getSize().y/2,650);
    settings.scale({1,0.5});
    centerOrigin(&settings);
    Text settingsText;
    settingsText.setFont(font); 
    settingsText.setString("Settings");
    settingsText.setCharacterSize(24); 
    settingsText.setFillColor(Color::Black);
    settingsText.setStyle(Text::Bold | Text::Underlined);
    settingsText.setPosition(settings.getPosition());
    centerTextOrigin(&settingsText);

    Sprite quit;
    spriteLoadFromFilePos(&quit,&boutonTexture,"./src/other/test.jpg",window.getSize().y/2,800);
    quit.scale({1,0.5});
    centerOrigin(&quit);
    Text quitText;
    quitText.setFont(font); 
    quitText.setString("Quit");
    quitText.setCharacterSize(24); 
    quitText.setFillColor(Color::Black);
    quitText.setStyle(Text::Bold | Text::Underlined);
    quitText.setPosition(quit.getPosition());
    centerTextOrigin(&quitText);


//  ------FIN MENU------  //

//  ------DEBUT SETTINGS------  //

    Sprite returnSettings;
    Texture returnSettingsTexture;
    spriteLoadFromFilePos(&returnSettings,&returnSettingsTexture,"./src/other/test.jpg",window.getSize().y/10,50);
    returnSettings.scale({0.5,0.3});
    centerOrigin(&returnSettings);
    Text returnSettingsText;
    returnSettingsText.setFont(font); 
    returnSettingsText.setString("Back");
    returnSettingsText.setCharacterSize(32); 
    returnSettingsText.setFillColor(Color::Black);
    returnSettingsText.setStyle(Text::Bold);
    returnSettingsText.setPosition(returnSettings.getPosition());
    centerTextOrigin(&returnSettingsText);
    
//  ------FIN SETTINGS------  //

    Sprite cursor;
    Texture cursorTexture;
    spriteLoadFromFilePos(&cursor,&cursorTexture,"./src/other/cursor.png",window.getSize().y/2,window.getSize().x/2);
    cursor.scale({0.01,0.01});
    window.setMouseCursorVisible(false);
    cursor.setOrigin({0.0,0.0});


    Level niv = Level();

    
    Car prev_car;   


    char s[256];
    while (window.isOpen())
    {
        Event event;
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            fenetre=0;
        }

        switch (fenetre)
        {
        case 3:
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();
                if(event.type == Event::MouseMoved)
                    updateCursorSprite(&cursor,&window);
                if (event.mouseButton.button == Mouse::Left && (change_key == "null"))
                {
                    if (IsSpriteCliked(returnSettings,&window)){
                        fenetre = 0;
                    }

                    for(auto i : game_keys.map_keys){
                        if(IsSpriteCliked(i.second.keySprite, &window)){
                            game_keys.button_is_pressed(i.first);
                            change_key = i.first;
                        }
                    }
                }
                
                if(event.type == Event::KeyPressed && (change_key != "null")){
                    game_keys.changeKey(change_key, event.key.code);
                    change_key = "null";
                }
                
            }
            window.clear();
                
            for(auto i : game_keys.map_keys){
                window.draw(i.second.keySprite);
                window.draw(i.second.keyText);
            }
            window.draw(returnSettings);
            window.draw(returnSettingsText);
            
            window.draw(cursor);
            window.display();
            break;
        case 2:
            if(niv.loaded==false){
                niv.loadTextures();
                niv.load("level/meroune/");
            }
            while (window.pollEvent(event))
            {     
                if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();
            }
            window.clear();
            
            if(niv.tabMode){
                for(auto i:niv.selectTile){
                    window.draw(i);
                }
            }
            else{
                for(auto i : niv.non_obstacles){
                    window.draw(i);
                }
                for(auto i : niv.obstacles){
                    window.draw(i);
                }

                window.draw(niv.creation);
            }

            niv.createLevel(&window,"level/meroune/");
            window.setMouseCursorVisible(true);
            window.display();
            break;
        case 1:
            if(niv.loaded==false){
                niv.loadTextures();
                niv.load("level/test/");
            }
            while (window.pollEvent(event))
            {     
                if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close(); 
            }

            //printf("started : %d\n",started);
            //printf("speed : %f\n",speed);
            //printf("rpm : %d\n",rpm);
            //printf("vitesse : %d\n",gear);
            char s[256];
            sprintf(s,"started : %s\nspeed : %f\nrpm : %d\nvitesse : %d\n",((car.started == 1) ? "true" : "false"),car.speed,car.rpm,car.gear);
            carInfo.setString(s);
            prev_car = car;
            car.move();
            car.deplacement(prev_car, &niv.obstacles);
            

            window.clear();
            for(auto i : niv.non_obstacles){
                window.draw(i);
            }
            for(auto i : niv.obstacles){
                window.draw(i);
            }
            window.draw(car.wheelLeft);
            window.draw(car.wheelRight);
            window.draw(car.rectangle);
            if(car.nocturne){
                printf("\nx %f  y %f\n\n\n", car.phares.getPosition().x, car.phares.getPosition().y);
                window.draw(car.phares);
            }
            window.draw(carInfo);
            window.draw(compteur);

            aiguille1.setRotation(170 + car.rpm*100/7500);
            aiguille2.setRotation(180 + abs(car.speed));

            window.draw(aiguille1);
            window.draw(aiguille2);



            window.display();
            break;
        default:
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (IsSpriteCliked(quit,&window)){
                        window.close();
                    }
                    if (IsSpriteCliked(play,&window)){
                        fenetre = 1;
                    }
                    if (IsSpriteCliked(settings,&window)){
                        fenetre = 3;
                    }
                    if (IsSpriteCliked(levelCreator,&window)){
                        niv.clicked=true;
                        fenetre = 2;
                    }
                }
                
            }
            updateCursorSprite(&cursor,&window);
            window.clear();
            window.draw(play);
            window.draw(upgrade);
            window.draw(quit);
            window.draw(settings);
            window.draw(playText);
            window.draw(upgradeText);
            window.draw(levelCreator);
            window.draw(levelCreatorText);
            window.draw(quitText);
            window.draw(settingsText);
            window.draw(cursor);
            window.display();
            break;
        }



        
        }
    

    return 0;
}
