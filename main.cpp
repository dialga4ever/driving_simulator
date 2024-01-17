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
    RenderWindow window(VideoMode(1000, 1000), "Driving Simulator", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);

    int fenetre = 0;

    // Stockage des textures
    Level niv = Level();

    niv.loadTextures();

    niv.loadObstacles();


    Font font;
    if (!font.loadFromFile("src/font/arial.ttf"))
    {
        printf("pas de font");
    }



    Keys game_keys = Keys(&window, font);
    string change_key = "null";
    
    Car car(500, 500, false, &game_keys);// Création de la voiture


    Text carInfo;
    carInfo.setFont(font); 
    carInfo.setString("Info");
    carInfo.setCharacterSize(24); 
    carInfo.setFillColor(Color::White);
    carInfo.setStyle(Text::Bold | Text::Underlined);
    carInfo.setPosition(0,0);



//  ------MENU------  //



    Sprite play;
    Texture playTexture;
    centerOrigin(&play);
    spriteLoadFromFilePos(&play,&playTexture,"./src/texture/test.jpg",window.getSize().y/2,200);
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

    Sprite upgrade;
    Texture upgradeTexture;
    spriteLoadFromFilePos(&upgrade,&upgradeTexture,"./src/texture/test.jpg",window.getSize().y/2,450);
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
    Texture settingsTexture;
    spriteLoadFromFilePos(&settings,&settingsTexture,"./src/texture/test.jpg",window.getSize().y/2,600);
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
    Texture quitTexture;
    spriteLoadFromFilePos(&quit,&quitTexture,"./src/texture/test.jpg",window.getSize().y/2,750);
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
    spriteLoadFromFilePos(&returnSettings,&returnSettingsTexture,"./src/texture/test.jpg",window.getSize().y/10,50);
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
    spriteLoadFromFilePos(&cursor,&cursorTexture,"./src/texture/cursor.png",window.getSize().y/2,window.getSize().x/2);
    cursor.scale({0.01,0.01});
    window.setMouseCursorVisible(false);
    


     // Stockage des textures
    Level niv = Level();

    
    Car prev_car;   


    char s[256];
    while (window.isOpen())
    {
        Event event;
        switch (fenetre)
        {
        case 2:
            if(niv.loaded==false){
                niv.loadTextures();
                niv.load("level/test/");
            }
            while (window.pollEvent(event))
            {     
                if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();
            }
            window.clear();
            for(auto i : niv.non_obstacles){
                window.draw(i);
            }
            for(auto i : niv.obstacles){
                window.draw(i);
            }
            niv.createLevel(&window,"level/test/");
            window.draw(niv.creation);
            window.setMouseCursorVisible(true);
            window.display();
            break;
        case 1:
            if(niv.loaded==false){
                niv.loadTextures();
                niv.loadObstacles();
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

            window.display();
            break;



        




        case 3:

            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();


                if(event.type == Event::MouseMoved)
                    updateCursorSprite(&cursor,&window);

                if (event.mouseButton.button == Mouse::Left)
                {
                    if (IsSpriteCliked(returnSettings,&window)){
                        fenetre = 0;
                    }

                    for(auto i : game_keys.map_keys){
                        if(IsSpriteCliked(i.second.keySprite, &window)){
                            
                            printf("ton père mérouane\n");
                            game_keys.button_is_pressed(i.first);
                            change_key = i.first;
                        }
                    }
                }
                
                if(event.type == Event::KeyPressed && (change_key != "null")){
                    printf("ta mère aures\nChange %d to %d", game_keys.map_keys[change_key].keyCode, event.key.code);
                    game_keys.changeKey(change_key, event.key.code);
                    printf("ta mère aures\nAfter change %d", game_keys.map_keys[change_key].keyCode);
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
                    if (IsSpriteCliked(upgrade,&window)){
                        fenetre = 2;
                    }
                }
                if(event.type == Event::MouseMoved)
                    updateCursorSprite(&cursor,&window);
            }

            window.clear();
            window.draw(play);
            window.draw(upgrade);
            window.draw(quit);
            window.draw(settings);
            window.draw(playText);
            window.draw(upgradeText);
            window.draw(quitText);
            window.draw(settingsText);
            window.draw(cursor);
            window.display();
            break;
        }



        
    }

    return 0;
}
