
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
    };
    public:
    map<String, Button> map_keys;
    Font font;
    Texture button;
    Texture buttonPressed;

    Keys();
    Keys(RenderWindow* window, Font font);
    void button_is_pressed(string key);
    void changeKey(string key, Keyboard::Key newKey);

};