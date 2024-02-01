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
        float window_x;
        float window_y;
        
        ChoixMap(int window_x, int window_y, sf::Font font);

        void mettre_a_jour();

        void createButton(string nom, Vector2f pos);


};
