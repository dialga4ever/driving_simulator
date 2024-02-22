
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

        std::map<std::string, sf::Texture> textures;
        std::map<std::string, Item> items;

        std::map<std::string, sf::Text> texts;

        sf::Texture etoile;

        Victory(int window_x, int window_y, sf::Font font);

        void load(std::string map_name, int nb_points);

        void loadTexture(std::string nom, std::string texture_path);

        void createText(std::string nom, std::string text, sf::Vector2f pos);

        void createItem(std::string nom, std::string text, sf::Texture* texture, sf::Vector2f pos, float scale_x = 1, float scale_y = 1);
};