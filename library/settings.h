
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>

using namespace std;
using namespace sf;




class Keys{

    struct Button{
        Keyboard::Key keyCode;
        Sprite keySprite;
        Text keyText;
        string keyNom;
    };
    public:
    map<String, Button> map_keys;
    Font font;
    Texture button;
    Texture buttonPressed;

    Sprite returnSettings;
    Texture returnSettingsTexture;
    Text returnSettingsText;

    Keys();
    Keys(RenderWindow* window, Font font);

    void createButton(string nom, Keyboard::Key key, Vector2f pos, RenderWindow* window);

    void button_is_pressed(string key);

    void changeKey(string key, Keyboard::Key newKey);

    string fromKeytoSring(const sf::Keyboard::Key k);

};

