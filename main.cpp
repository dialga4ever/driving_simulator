#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "library/car.h"
#include "library/textureUtility.h"

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

    int fenetre =0;


    Car car(500, 500);// Création de la voiture

    Font font;
    if (!font.loadFromFile("src/font/arial.ttf"))
    {
        printf("pas de font");
    }

    
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


    Sprite cursor;
    Texture cursorTexture;
    spriteLoadFromFilePos(&cursor,&cursorTexture,"./src/texture/cursor.png",window.getSize().y/2,window.getSize().x/2);
    cursor.scale({0.1,0.1});
    window.setMouseCursorVisible(false);


    while (window.isOpen())
    {
        Event event;
        switch (fenetre)
        {
        case 1:
            while (window.pollEvent(event))
            {     
                if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Delete)))
                    window.close();


                
            }
            car.move();
            car.deceleration();
            car.deplacement();

            window.clear();
            window.draw(car.rectangle);
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
                }
                if(event.type == Event::MouseMoved)
                    updateCursorSprite(&cursor,&window);
            }

            window.clear();
            window.draw(play);
            window.draw(upgrade);
            window.draw(quit);
            window.draw(playText);
            window.draw(upgradeText);
            window.draw(quitText);
            window.draw(cursor);

            window.display();
            break;
        }



        
    }

    return 0;
}
