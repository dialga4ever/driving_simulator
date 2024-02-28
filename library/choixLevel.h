#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include "textureUtility.h"


using namespace std;
using namespace sf;

struct Item{
        sf::Sprite sprite;
};
class ChoixMap{
    public:
        struct Button{
            Sprite choix_map_sprite;
            Text choix_map_text;
        };
        Font font;
        map<string, Button> list_map;
        Texture texture;
        float window_x;
        float window_y;
        std::map<std::string, Item> items;
        
        std::map<std::string, sf::Texture> textures;
        ChoixMap(int window_x, int window_y, sf::Font font);

        void mettre_a_jour();

        void createButton(string nom, Vector2f pos);
        void loadTexture(std::string nom, std::string texture_path);
        void createItem(std::string nom, sf::Texture* texture, sf::Vector2f pos);
        void updateStar(int window_x_, int window_y_);
};
