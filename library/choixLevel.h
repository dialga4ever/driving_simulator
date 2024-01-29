#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include "textureUtility.h"


using namespace std;
using namespace sf;


class ChoixMap{
    public:
        struct Button{
            Sprite choix_map_sprite;
            Texture choix_map_texture;
            Text choix_map_text;
        };

        map<string, Button> list_map;
        bool loaded;
        
        ChoixMap(sf::RenderWindow* window, sf::Font font);

        void mettre_a_jour(RenderWindow *window, sf::Font font);

        void createButton(string nom, Vector2f pos, sf::RenderWindow* window, sf::Font font);


};
