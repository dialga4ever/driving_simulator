#include "settings.h"
#include "textureUtility.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;


Keys::Keys(){}

Keys::Keys(RenderWindow* window, Font font_){
    font = font_;

    button.loadFromFile("src/other/touche.png");
    buttonPressed.loadFromFile("src/other/test.jpg");
    int y = 100;

    Button left;
    left.keyCode = Keyboard::Left;
    left.keySprite.setTexture(button);
    left.keySprite.setPosition({(window->getSize().x/4),y});
    left.keySprite.scale({0.5,0.5});
    centerOrigin(&left.keySprite);
    left.keyText.setFont(font); 
    left.keyText.setString("Left : "+left.keyText.getString());
    left.keyText.setCharacterSize(16); 
    left.keyText.setFillColor(Color::Black);
    left.keyText.setStyle(Text::Bold);
    left.keyText.setPosition(left.keySprite.getPosition());
    centerTextOrigin(&left.keyText);
    y += 100;
    map_keys.insert({"left", left});

    Button right;
    right.keyCode = Keyboard::Right;
    right.keySprite.setTexture(button);
    right.keySprite.setPosition({(window->getSize().x/4),y});
    right.keySprite.scale({0.5,0.5});
    right.keySprite.scale({0.5,0.5});
    centerOrigin(&right.keySprite);
    right.keyText.setFont(font); 
    right.keyText.setString("Right : "+right.keyText.getString());
    right.keyText.setCharacterSize(16); 
    right.keyText.setFillColor(Color::Black);
    right.keyText.setStyle(Text::Bold);
    right.keyText.setPosition(right.keySprite.getPosition());
    centerTextOrigin(&right.keyText);
    y += 100;
    map_keys["right"] = right;


    Button up;
    up.keyCode = Keyboard::Up;
    up.keySprite.setTexture(button);
    up.keySprite.setPosition({(window->getSize().x/4),y});
    up.keySprite.scale({0.5,0.5});
    centerOrigin(&up.keySprite);
    up.keyText.setFont(font); 
    up.keyText.setString("Up : "+up.keyText.getString());
    up.keyText.setCharacterSize(16); 
    up.keyText.setFillColor(Color::Black);
    up.keyText.setStyle(Text::Bold);
    up.keyText.setPosition(up.keySprite.getPosition());
    centerTextOrigin(&up.keyText);
    y += 100;
    map_keys["up"] = up;


    Button down;
    down.keyCode = Keyboard::Down;
    down.keySprite.setTexture(button);
    down.keySprite.setPosition({(window->getSize().x/4),y});
    down.keySprite.scale({0.5,0.5});
    centerOrigin(&down.keySprite);
    down.keyText.setFont(font); 
    down.keyText.setString("Down : "+down.keyText.getString());
    down.keyText.setCharacterSize(16); 
    down.keyText.setFillColor(Color::Black);
    down.keyText.setStyle(Text::Bold);
    down.keyText.setPosition(down.keySprite.getPosition());
    centerTextOrigin(&down.keyText);
    y += 100;
    map_keys["down"] = down;


    Button start;
    start.keyCode = Keyboard::E;
    start.keySprite.setTexture(button);
    start.keySprite.setPosition({(window->getSize().x/4),y});
    start.keySprite.scale({0.5,0.5});
    centerOrigin(&start.keySprite);
    start.keyText.setFont(font); 
    start.keyText.setString("Start : "+start.keyText.getString());
    start.keyText.setCharacterSize(16); 
    start.keyText.setFillColor(Color::Black);
    start.keyText.setStyle(Text::Bold);
    start.keyText.setPosition(start.keySprite.getPosition());
    centerTextOrigin(&start.keyText);
    y += 100;
    map_keys["start"] = start;
    
    Button clutch;
    clutch.keyCode = Keyboard::LShift;
    clutch.keySprite.setTexture(button);
    clutch.keySprite.setPosition({(window->getSize().x/4),y});
    clutch.keySprite.scale({0.5,0.5});
    centerOrigin(&left.keySprite);
    clutch.keyText.setFont(font); 
    clutch.keyText.setString("Clutch : "+clutch.keyText.getString());
    clutch.keyText.setCharacterSize(16); 
    clutch.keyText.setFillColor(Color::Black);
    clutch.keyText.setStyle(Text::Bold);
    clutch.keyText.setPosition(clutch.keySprite.getPosition());
    centerTextOrigin(&clutch.keyText);
    y += 100;
    map_keys["clutch"] = clutch;
    
    Button gear0;
    gear0.keyCode = Keyboard::Num0;
    gear0.keySprite.setTexture(button);
    gear0.keySprite.setPosition({(window->getSize().x/4),y});
    gear0.keySprite.scale({0.5,0.5});
    centerOrigin(&left.keySprite);
    gear0.keyText.setFont(font); 
    gear0.keyText.setString("Gear0 : "+gear0.keyText.getString());
    gear0.keyText.setCharacterSize(16); 
    gear0.keyText.setFillColor(Color::Black);
    gear0.keyText.setStyle(Text::Bold);
    gear0.keyText.setPosition(gear0.keySprite.getPosition());
    centerTextOrigin(&gear0.keyText);
    y += 100;
    map_keys["gear0"] = gear0;
    
    Button gear1;
    gear1.keyCode = Keyboard::Num1;
    gear1.keySprite.setTexture(button);
    gear1.keySprite.setPosition({(window->getSize().x/4),y});
    gear1.keySprite.scale({0.5,0.5});
    centerOrigin(&gear1.keySprite);
    gear1.keyText.setFont(font); 
    gear1.keyText.setString("Gear1 : "+gear1.keyText.getString());
    gear1.keyText.setCharacterSize(16); 
    gear1.keyText.setFillColor(Color::Black);
    gear1.keyText.setStyle(Text::Bold);
    gear1.keyText.setPosition(gear1.keySprite.getPosition());
    centerTextOrigin(&gear1.keyText);
    y += 100;
    map_keys["gear1"] = gear1;
    
    Button gear2;
    gear2.keyCode = Keyboard::Num2;
    gear2.keySprite.setTexture(button);
    gear2.keySprite.setPosition({(window->getSize().x/4),y});
    gear2.keySprite.scale({0.5,0.5});
    centerOrigin(&gear2.keySprite);
    gear2.keyText.setFont(font); 
    gear2.keyText.setString("Gear2 : "+gear2.keyText.getString());
    gear2.keyText.setCharacterSize(16); 
    gear2.keyText.setFillColor(Color::Black);
    gear2.keyText.setStyle(Text::Bold);
    gear2.keyText.setPosition(gear2.keySprite.getPosition());
    centerTextOrigin(&gear2.keyText);
    y += 100;
    map_keys["gear2"] = gear2;
    
    Button gear3;
    gear3.keyCode = Keyboard::Num3;
    gear3.keySprite.setTexture(button);
    gear3.keySprite.setPosition({(window->getSize().x/4),y});
    gear3.keySprite.scale({0.5,0.5});
    centerOrigin(&gear3.keySprite);
    gear3.keyText.setFont(font); 
    gear3.keyText.setString("Gear3 : "+gear3.keyText.getString());
    gear3.keyText.setCharacterSize(16); 
    gear3.keyText.setFillColor(Color::Black);
    gear3.keyText.setStyle(Text::Bold);
    gear3.keyText.setPosition(gear3.keySprite.getPosition());
    centerTextOrigin(&gear3.keyText);
    y += 100;
    map_keys["gear3"] = gear3;
    
    Button gear_back_1;
    gear_back_1.keyCode = Keyboard::BackSpace;
    gear_back_1.keySprite.setTexture(button);
    gear_back_1.keySprite.setPosition({(window->getSize().x/4),y});
    gear_back_1.keySprite.scale({0.5,0.5});
    centerOrigin(&gear_back_1.keySprite);
    gear_back_1.keyText.setFont(font); 
    gear_back_1.keyText.setString("Gear back 1 : "+gear_back_1.keyText.getString());
    gear_back_1.keyText.setCharacterSize(16); 
    gear_back_1.keyText.setFillColor(Color::Black);
    gear_back_1.keyText.setStyle(Text::Bold);
    gear_back_1.keyText.setPosition(gear_back_1.keySprite.getPosition());
    centerTextOrigin(&gear_back_1.keyText);
    y += 100;
    map_keys["gear_back_1"] = gear_back_1;
}

void Keys::button_is_pressed(string key){
    map_keys[key].keySprite.setTexture(buttonPressed);
}

void Keys::changeKey(string key, Keyboard::Key newKey){

    map_keys[key].keyCode = newKey;

    map_keys[key].keySprite.setTexture(button);
}