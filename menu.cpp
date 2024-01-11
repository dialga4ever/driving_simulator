#include <SFML/Graphics.hpp>
#include "library/textureUtility.h"


using namespace std;
using namespace sf;


bool IsSpriteCliked(Sprite tarket,RenderWindow *window){
    return tarket.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
}
void updateCursorSprite(Sprite *tarket,RenderWindow *window){
    tarket->setPosition(static_cast<Vector2f>(Mouse::getPosition(*window)));
}



int main()
{
    Font font;
    if (!font.loadFromFile("src/font/arial.ttf"))
    {
        printf("pas de font");
    }

    RenderWindow window(VideoMode(1000, 1000), "Driving Simulator", Style::Titlebar | Style::Close);
    
    Sprite play;
    Texture playTexture;
    spriteLoadFromFilePos(&play,&playTexture,"./src/texture/test.jpg",window.getSize().y/2,200);
    play.scale({1,0.5});
    centerOrigin(&play);
    Text playText;
    playText.setFont(font); 
    playText.setString("Select level");
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
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.mouseButton.button == Mouse::Left)
            {
                if (IsSpriteCliked(quit,&window)){
                    window.close();
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
    }

    return 0;
}
