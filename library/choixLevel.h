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
            Text choix_map_text;
        };
        Font font;
        map<string, Button> list_map;
        Texture texture;
        bool loaded;
        
        ChoixMap(sf::Font font);

        void mettre_a_jour(sf::Font font);

        void createButton(string nom, Vector2f pos, sf::Font font);


};
