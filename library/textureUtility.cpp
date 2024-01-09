#include <SFML/Graphics.hpp>
#include <iostream>

void spriteLoadFromFilePos(sf::Sprite *self,sf::Texture *quitTexture,const std::string &filename,int x,int y)
{
    printf("test\n");
    if (!quitTexture->loadFromFile(filename))
    {
        std::cout << "Error: Couldn't load texture\n";
        
    }
    self->setTexture(*quitTexture);
    self->setPosition({float(x),float(y)});
}
void centerOrigin(sf::Sprite *self){
    sf::FloatRect test = self->getLocalBounds();
    self->setOrigin(test.left + test.width/2.0f,test.top  + test.height/2.0f);
}