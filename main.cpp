#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "library/car.h"
#include "library/textureUtility.h"
#include "library/levelLoader.h"
#include "library/choixLevel.h"
#include "library/menu.h"
#include "library/victory.h"


using namespace std;
using namespace sf;

#define PI 3.14159265


bool IsSpriteCliked(Sprite target,RenderWindow *window){
    //check if the left mouse button is pressed
    if(!Mouse::isButtonPressed(Mouse::Left))
        return false;
    return target.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
}
void updateCursorSprite(Sprite *target,RenderWindow *window){
    target->setPosition(static_cast<Vector2f>(Mouse::getPosition(*window)));
}


int main(){
    RenderWindow window(VideoMode(1024, 1024), "Driving Simulator", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);

    Sprite cursor;
    Texture cursorTexture;
    spriteLoadFromFilePos(&cursor,&cursorTexture,"./src/other/cursor.png",window.getSize().y/2,window.getSize().x/2);
    cursor.scale({0.01,0.01});
    window.setMouseCursorVisible(false);
    cursor.setOrigin({0.0,0.0});

    int fenetre = 0;
    int next_fenetre = 0;

    Font font;
    if (!font.loadFromFile("src/font/arial.ttf"))
        printf("pas de font");

    ChoixMap choix_niveaux(window.getSize().x, window.getSize().y, font);
    string path;

    Menu menu(window.getSize().x, window.getSize().y, font);

    Victory victory(window.getSize().x, window.getSize().y, font);

    Keys game_keys = Keys(&window, font);
    string change_key = "null";
    
    Car car=Car(0, 512, 512, false, &game_keys, &window, font);

    Level niv = Level();
    niv.loadTextures();
    //elapsed time
    std::chrono::seconds elapsed;
    bool realesed = true;

    char s[256];
    while (window.isOpen()){
        Event event;
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            fenetre=0;
            niv.loaded = false;
        }
        switch (fenetre){


        case 5:    //Victoire
            if(!victory.loaded){
                victory.load(path, car.nb_point, elapsed);
            }
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();
                if(event.type == Event::MouseMoved)
                    updateCursorSprite(&cursor,&window);
                if (event.mouseButton.button == Mouse::Left)
                { 
                    if (IsSpriteCliked(victory.items.at("rejouer").sprite,&window)){
                        fenetre = 1;
                    }
                    if (IsSpriteCliked(victory.items.at("menu").sprite,&window)){
                        fenetre = 0;
                    }
                }
            }
            window.clear();
            for(auto i : niv.non_obstacles){
                window.draw(i);
            }
            for(auto i : niv.obstacles){
                window.draw(i);
            }
            for(auto i : niv.decos){
                window.draw(i);
            }

            window.draw(victory.items.at("ombre").sprite);
            for(auto i : victory.items){
                if(i.first != "ombre"){
                    window.draw(i.second.sprite);
                    window.draw(i.second.text);
                }
            }

            for(auto i : victory.texts){
                window.draw(i.second);
            }

            window.draw(cursor);

            window.display();
            break;


        case 4:    //Choix de niveau
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();
                if(event.type == Event::MouseMoved)
                    updateCursorSprite(&cursor,&window);
                if (event.mouseButton.button == Mouse::Left&&realesed)
                { 
                    for(auto i : choix_niveaux.list_map){
                        if (IsSpriteCliked(i.second.choix_map_sprite,&window)){
                            path = i.first;
                            fenetre = next_fenetre;
                        }
                    }
                }
                if(!event.mouseButton.button){  
                    realesed = true;
                }
            }




            window.clear();
            window.draw(menu.background_alt_sprite);
            for(auto i : choix_niveaux.list_map){
                window.draw(i.second.choix_map_sprite);
                window.draw(i.second.choix_map_text);
                
            }
            for(auto j : choix_niveaux.items){
                window.draw(j.second.sprite);
            }

            window.draw(cursor);

            window.display();
            break;


        case 3:    //Settings
            while (window.pollEvent(event)){
                if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();
                if(event.type == Event::MouseMoved)
                    updateCursorSprite(&cursor,&window);
                if (event.mouseButton.button == Mouse::Left && (change_key == "null"))
                {
                    if (IsSpriteCliked(game_keys.returnSettings,&window))
                        fenetre = 0;
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
            window.draw(menu.background_alt_sprite);
            for(auto i : game_keys.map_keys){
                window.draw(i.second.keySprite);
                window.draw(i.second.keyText);
            }
            window.draw(game_keys.returnSettings);
            window.draw(game_keys.returnSettingsText);
            
            window.draw(cursor);
            window.display();
            break;


        case 2:    //Creation de niveau
            if(niv.loaded==false)
            {
                niv.clicked=true;
                niv.load("level/"+path+"/");
            }
            
            while (window.pollEvent(event)){     
                if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();
            }
            window.clear();
            
            if(niv.tabMode==true){
                for(auto i:niv.selectTile){
                    window.draw(i);
                }
            }else{
                for(auto i : niv.non_obstacles){
                    window.draw(i);
                }
                for(auto i : niv.obstacles){
                    window.draw(i);
                }
                window.draw(niv.car);
                for(auto i : niv.decos){
                    window.draw(i);
                }
                for(auto i : niv.places_parking){
                    window.draw(i);
                }
                window.draw(niv.creation);
            }

            niv.createLevel(&window,"level/"+path+"/");
            window.setMouseCursorVisible(true);
            window.display();
            break;


        case 1:    //Jeu de base
            if(niv.loaded==false){
                niv.load("level/"+path+"/");
                car.x = niv.car.getPosition().x;
                car.y = niv.car.getPosition().y;
                car.defaultAngle = niv.car.getRotation();
                car.reinisialisationCar();

            }

            while (window.pollEvent(event)){     
                if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close(); 
            }

            if(car.win){
                fenetre = 5;
                niv.loaded=false;
                //get the time of the car (start_time) and the time of the end of the game
                auto end_time = chrono::system_clock::now();
                elapsed = chrono::duration_cast<chrono::seconds>(end_time - car.start_time);
            }
            car.move();
            car.deplacement( &niv.obstacles, &niv.places_parking);

            window.clear();
            for(auto i : niv.non_obstacles){
                window.draw(i);
            }
            for(auto i : niv.obstacles){
                window.draw(i);
            }

            for(auto i : niv.places_parking){
                window.draw(i);
            }
            window.draw(car.wheelLeft);
            window.draw(car.wheelRight);
            window.draw(car.rectangle);
            if(car.nocturne)
                window.draw(car.phares);
            
            for(auto i : niv.decos){
                window.draw(i);
            }
            
            
            window.draw(car.fondCarInfo);
            window.draw(car.carInfo);
            window.draw(car.compteur);
            window.draw(car.aiguille1);
            window.draw(car.aiguille2);

            window.display();
            break;
        default://Menu principal
            while (window.pollEvent(event)){
                if (event.type == Event::Closed)
                    window.close();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (IsSpriteCliked(menu.list_menu.at("Quit").choix_menu_sprite,&window)){
                        window.close();
                    }
                    if (IsSpriteCliked(menu.list_menu.at("Settings").choix_menu_sprite,&window)){
                        fenetre = 3;//Settings
                    }
                    if (IsSpriteCliked(menu.list_menu.at("Level Creator").choix_menu_sprite,&window)){
                        niv.clicked=true;
                        fenetre = 4;
                        choix_niveaux.updateStar(window.getSize().x, window.getSize().y);

                        realesed=false;
                        next_fenetre = 2;//Creation de niveau
                    }
                    if (IsSpriteCliked(menu.list_menu.at("Play").choix_menu_sprite,&window)){
                        choix_niveaux.updateStar(window.getSize().x, window.getSize().y);
                        fenetre = 4;
                        realesed=false;
                        next_fenetre = 1;//Jeu de base
                    }
                }
            }
            updateCursorSprite(&cursor,&window);
            window.clear();
            window.draw(menu.background_sprite);
            for(auto i : menu.list_menu){
                window.draw(i.second.choix_menu_sprite);
                window.draw(i.second.choix_menu_text);
            }

            window.draw(cursor);
            window.display();
            break;
        }
    }
    

    return 0;
}
