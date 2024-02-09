#include <SFML/Graphics.hpp>
#include "textureUtility.h"
#include "menu.h"

using namespace std;
using namespace sf;


/*bool IsSpriteCliked(Sprite tarket,RenderWindow *window){
    return tarket.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
}
void updateCursorSprite(Sprite *tarket,RenderWindow *window){
    tarket->setPosition(static_cast<Vector2f>(Mouse::getPosition(*window)));
}*/

Menu::Menu(int window_x_, int window_y_, sf::Font font_){
    font = font_;
    window_x = (float)window_x_;
    window_y = (float)window_y_;
    int nb_button = 6;

    texture.loadFromFile("src/other/bouton.png");
    background.loadFromFile("src/other/background.png");
    background_sprite.setTexture(background);
    background_sprite.setPosition({0,0});



    createButton("Play", {window_x/2, 300});
    createButton("Level Creator", {window_x/2, 750});
    createButton("Upgrade", {window_x/2, 825});
    list_menu.at("Upgrade").choix_menu_sprite.setColor(Color(255, 255, 255, 100));
    createButton("Settings", {window_x/2, 900});
    createButton("Quit", {window_x/2, 975});
}


void Menu::createButton(string nom, Vector2f pos){
    Button self;
    self.choix_menu_sprite.setTexture(texture);
    self.choix_menu_sprite.setPosition(pos);
    self.choix_menu_sprite.scale({1,0.5});
    centerOrigin(&self.choix_menu_sprite);
    self.choix_menu_text.setFont(font);
    self.choix_menu_text.setString((sf::String)nom);
    self.choix_menu_text.setCharacterSize(16);
    self.choix_menu_text.setFillColor(Color::Black);
    self.choix_menu_text.setStyle(Text::Bold);
    self.choix_menu_text.setPosition(self.choix_menu_sprite.getPosition());
    centerTextOrigin(&self.choix_menu_text);
    list_menu.insert({nom, self});
}


