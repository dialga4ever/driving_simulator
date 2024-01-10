#include <SFML/Graphics.hpp>
#include "library/textureUtility.h"

bool IsSpriteCliked(sf::Sprite tarket,sf::RenderWindow *window){
    return tarket.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}
void updateCursorSprite(sf::Sprite *tarket,sf::RenderWindow *window){
    tarket->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)));

}



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Driving Simulator", sf::Style::Titlebar | sf::Style::Close);
    

    sf::Sprite quit;
    sf::Texture quitTexture;
    spriteLoadFromFilePos(&quit,&quitTexture,"./src/texture/test.jpg",window.getSize().y/2,window.getSize().x/2);
    quit.scale({1,0.5});
    centerOrigin(&quit);
    quit.setColor(sf::Color::Red);


    sf::Sprite cursor;
    sf::Texture cursorTexture;
    spriteLoadFromFilePos(&cursor,&cursorTexture,"./src/texture/cursor.png",window.getSize().y/2,window.getSize().x/2);
    cursor.scale({0.1,0.1});

    window.setMouseCursorVisible(false);
    


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (IsSpriteCliked(quit,&window)){
                    window.close();
                }
            }
            if(event.type == sf::Event::MouseMoved)
                updateCursorSprite(&cursor,&window);
        }

        window.clear();
        window.draw(quit);
        window.draw(cursor);
        window.display();
    }

    return 0;
}
