#include <SFML/Graphics.hpp>
#include "library/textureUtility.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Driving Simulator");
    

    sf::Sprite quit;
    sf::Texture quitTexture;
    
    spriteLoadFromFilePos(&quit,&quitTexture,"./src/texture/test.jpg",window.getSize().y/2,window.getSize().x/2);


    quit.scale({1,0.5});

    centerOrigin(&quit);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(quit);
        window.display();
    }

    return 0;
}
