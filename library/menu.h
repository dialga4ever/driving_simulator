#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <vector>

class Menu{
    public:
        struct Button{
            sf::Sprite choix_menu_sprite;
            sf::Text choix_menu_text;
        };
        sf::Texture texture;
        sf::Texture background;
        sf::Sprite background_sprite;
        sf::Font font;
        std::map<std::string, Button> list_menu;
        float window_x;
        float window_y;


        Menu(int window_x, int window_y, sf::Font font);

        void createButton(std::string nom, sf::Vector2f pos);
};