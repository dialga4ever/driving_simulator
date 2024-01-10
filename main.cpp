#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "library/car.h"
#include "library/textureUtility.h"

using namespace std;
using namespace sf;

#define PI 3.14159265

bool IsSpriteCliked(sf::Sprite tarket,sf::RenderWindow *window){
    return tarket.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}
void updateCursorSprite(sf::Sprite *tarket,sf::RenderWindow *window){
    tarket->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)));
}





int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Driving Simulator", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    int fenetre =0;


    Car car(500, 500);// Création de la voiture

    sf::Font font;
    if (!font.loadFromFile("src/font/arial.ttf"))
    {
        printf("pas de font");
    }

    
    sf::Sprite play;
    sf::Texture playTexture;
    centerOrigin(&play);
    spriteLoadFromFilePos(&play,&playTexture,"./src/texture/test.jpg",window.getSize().y/2,200);
    play.scale({1,0.5});
    centerOrigin(&play);
    sf::Text playText;
    playText.setFont(font); 
    playText.setString("Play");
    playText.setCharacterSize(24); 
    playText.setFillColor(sf::Color::Black);
    playText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    playText.setPosition(play.getPosition());
    centerTextOrigin(&playText);


    sf::Sprite upgrade;
    sf::Texture upgradeTexture;
    spriteLoadFromFilePos(&upgrade,&upgradeTexture,"./src/texture/test.jpg",window.getSize().y/2,450);
    upgrade.scale({1,0.5});
    centerOrigin(&upgrade);
    upgrade.setColor(sf::Color(255, 255, 255, 100));
    sf::Text upgradeText;
    upgradeText.setFont(font); 
    upgradeText.setString("Upgrade car");
    upgradeText.setCharacterSize(24); 
    upgradeText.setFillColor(sf::Color::Black);
    upgradeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    upgradeText.setPosition(upgrade.getPosition());
    centerTextOrigin(&upgradeText);
    

    sf::Sprite quit;
    sf::Texture quitTexture;
    spriteLoadFromFilePos(&quit,&quitTexture,"./src/texture/test.jpg",window.getSize().y/2,750);
    quit.scale({1,0.5});
    centerOrigin(&quit);
    sf::Text quitText;
    quitText.setFont(font); 
    quitText.setString("Quit");
    quitText.setCharacterSize(24); 
    quitText.setFillColor(sf::Color::Black);
    quitText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    quitText.setPosition(quit.getPosition());
    centerTextOrigin(&quitText);


    sf::Sprite cursor;
    sf::Texture cursorTexture;
    spriteLoadFromFilePos(&cursor,&cursorTexture,"./src/texture/cursor.png",window.getSize().y/2,window.getSize().x/2);
    cursor.scale({0.1,0.1});
    window.setMouseCursorVisible(false);


    while (window.isOpen())
    {
        sf::Event event;
        switch (fenetre)
        {
        case 1:
            while (window.pollEvent(event))
            {     
                if (event.type == Event::Closed)
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
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (IsSpriteCliked(quit,&window)){
                        window.close();
                    }
                    if (IsSpriteCliked(play,&window)){
                        fenetre = 1;
                    }
                }
                if(event.type == sf::Event::MouseMoved)
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
