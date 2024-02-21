
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>





class Victory {

    struct Item{
        sf::Sprite sprite;
        sf::Text text;
    };

    public:
        sf::Font font;
        float window_x;
        float window_y;
        bool loaded;
        std::vector<sf::Texture> textures;

        std::map<std::string, Item> items;
        std::map<std::string, sf::Text> texts;

        Victory(int window_x, int window_y, sf::Font font);

        void load(std::string map_name);

        void createText(std::string nom, std::string text, sf::Vector2f pos);

        void createItem(std::string nom, std::string text, std::string texture_path, sf::Vector2f pos);
};