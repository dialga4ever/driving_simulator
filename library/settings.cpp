#include "settings.h"
#include "textureUtility.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <fstream>




using namespace std;
using namespace sf;


Keys::Keys(){
    ifstream file;
    file.open("src/other/settings.ini");
    // Vérifier si le fichier est ouvert
    if (file.is_open()) {
        string key;
        string value;
        while (file >> key >> value) {
            map_keys[key].keyCode = fromStringToKey(value);
            map_keys[key].keyText.setString(map_keys[key].keyNom + " : " + fromKeytoSring(map_keys[key].keyCode));
        }
        // Fermer le fichier après la lecture
        file.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
}

void Keys::createButton(string nom, Keyboard::Key key, Vector2f pos){
    Button self;
    self.keyCode = key;
    self.keySprite.setTexture(button);
    self.keySprite.setPosition(pos);
    self.keySprite.scale({1,0.5});
    centerOrigin(&self.keySprite);
    self.keyNom = nom;
    self.keyText.setFont(font); 
    self.keyText.setString(nom + " : " + fromKeytoSring(key));
    self.keyText.setCharacterSize(16); 
    self.keyText.setFillColor(Color::Black);
    self.keyText.setStyle(Text::Bold);
    self.keyText.setPosition(self.keySprite.getPosition());
    centerTextOrigin(&self.keyText);
    map_keys.insert({nom, self});
}

Keys::Keys(RenderWindow* window, Font font_){
    font = font_;

    button.loadFromFile("src/other/touche.png");
    buttonPressed.loadFromFile("src/other/touchePressed.png");
    int y = 100;

    spriteLoadFromFilePos(&returnSettings,&returnSettingsTexture,"./src/other/boutonBack.jpg",window->getSize().y/10,50);
    returnSettings.scale({0.5,0.3});
    centerOrigin(&returnSettings);
    returnSettingsText.setFont(font); 
    returnSettingsText.setString("Back");
    returnSettingsText.setCharacterSize(32); 
    returnSettingsText.setFillColor(Color::Black);
    returnSettingsText.setStyle(Text::Bold);
    returnSettingsText.setPosition(returnSettings.getPosition());
    centerTextOrigin(&returnSettingsText);

    createButton("Left", Keyboard::Left, {(float)(window->getSize().x/3), 100});

    createButton("Right", Keyboard::Right, {(float)(window->getSize().x/3), 200});

    createButton("Up", Keyboard::Up, {(float)(window->getSize().x/3), 300});

    createButton("Down", Keyboard::Down, {(float)(window->getSize().x/3), 400});

    createButton("Start", Keyboard::E, {(float)(window->getSize().x/3), 500});

    createButton("Clutch", Keyboard::LShift, {(float)(window->getSize().x/3), 600});

    createButton("Gear0", Keyboard::Num0, {(float)(window->getSize().x/1.33), 100});

    createButton("Gear1", Keyboard::Num1, {(float)(window->getSize().x/1.33), 200});

    createButton("Gear2", Keyboard::Num2, {(float)(window->getSize().x/1.33), 300});

    createButton("Gear3", Keyboard::Num3, {(float)(window->getSize().x/1.33), 400});

    createButton("Gear back 1", Keyboard::BackSpace, {(float)(window->getSize().x/1.33), 500});
    ifstream file;
    file.open("src/other/settings.ini");
    // Vérifier si le fichier est ouvert
    if (file.is_open()) {
        string key;
        string value;
        while (file >> key >> value) {
            map_keys[key].keyCode = fromStringToKey(value);
            map_keys[key].keyText.setString(map_keys[key].keyNom + " : " + fromKeytoSring(map_keys[key].keyCode));
        }
        // Fermer le fichier après la lecture
        file.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
}

void Keys::button_is_pressed(string key){
    map_keys[key].keySprite.setTexture(buttonPressed);
}

void Keys::changeKey(string key, Keyboard::Key newKey){
    map_keys[key].keyCode = newKey;
    map_keys[key].keyText.setString(map_keys[key].keyNom + " : " + fromKeytoSring(newKey));
    map_keys[key].keySprite.setTexture(button);

    //save the new key in the file settings.ini
    ofstream file;
    file.open("src/other/settings.ini");
    // Vérifier si le fichier est ouvert
    if (file.is_open()) {
        // Parcourir la map et écrire les clés dans le fichier
        for (auto it = map_keys.begin(); it != map_keys.end(); it++) {
            file << it->first.toAnsiString() << " " << fromKeytoSring(it->second.keyCode) << std::endl;
        }
        // Fermer le fichier après l'écriture
        file.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
}

string Keys::fromKeytoSring(const sf::Keyboard::Key k){
    string ret;
    switch(k){
    case sf::Keyboard::A :
        ret="A";break;
    case sf::Keyboard::B :
        ret="B";break;
    case sf::Keyboard::C :
        ret="C";break;
    case sf::Keyboard::D :
        ret="D";break;
    case sf::Keyboard::E :
        ret="E";break;
    case sf::Keyboard::F :
        ret="F";break;
    case sf::Keyboard::G :
        ret="G";break;
    case sf::Keyboard::H :
        ret="H";break;
    case sf::Keyboard::I :
        ret="I";break;
    case sf::Keyboard::J :
        ret="J";break;
    case sf::Keyboard::K :
        ret="K";break;
    case sf::Keyboard::L :
        ret="L";break;
    case sf::Keyboard::M :
        ret="M";break;
    case sf::Keyboard::N :
        ret="N";break;
    case sf::Keyboard::O :
        ret="O";break;
    case sf::Keyboard::P :
        ret="P";break;
    case sf::Keyboard::Q :
        ret="Q";break;
    case sf::Keyboard::R :
        ret="R";break;
    case sf::Keyboard::S :
        ret="S";break;
    case sf::Keyboard::T :
        ret="T";break;
    case sf::Keyboard::U :
        ret="U";break;
    case sf::Keyboard::V :
        ret="V";break;
    case sf::Keyboard::W :
        ret="W";break;
    case sf::Keyboard::X :
        ret="X";break;
    case sf::Keyboard::Y :
        ret="Y";break;
    case sf::Keyboard::Z :
        ret="Z";break;
    case sf::Keyboard::Num0 :
        ret="Num0";break;
    case sf::Keyboard::Num1 :
        ret="Num1";break;
    case sf::Keyboard::Num2 :
        ret="Num2";break;
    case sf::Keyboard::Num3 :
        ret="Num3";break;
    case sf::Keyboard::Num4 :
        ret="Num4";break;
    case sf::Keyboard::Num5 :
        ret="Num5";break;
    case sf::Keyboard::Num6 :
        ret="Num6";break;
    case sf::Keyboard::Num7 :
        ret="Num7";break;
    case sf::Keyboard::Num8 :
        ret="Num8";break;
    case sf::Keyboard::Num9 :
        ret="Num9";break;
    case sf::Keyboard::Escape :
        ret="Escape";break;
    case sf::Keyboard::LControl :
        ret="LControl";break;
    case sf::Keyboard::LShift :
        ret="LShift";break;
    case sf::Keyboard::LAlt :
        ret="LAlt";break;
    case sf::Keyboard::LSystem :
        ret="LSystem";break;
    case sf::Keyboard::RControl :
        ret="RControl";break;
    case sf::Keyboard::RShift :
        ret="RShift";break;
    case sf::Keyboard::RAlt :
        ret="RAlt";break;
    case sf::Keyboard::RSystem :
        ret="RSystem";break;
    case sf::Keyboard::Menu :
        ret="Menu";break;
    case sf::Keyboard::LBracket :
        ret="LBracket";break;
    case sf::Keyboard::RBracket :
        ret="RBracket";break;
    case sf::Keyboard::SemiColon :
        ret="SemiColon";break;
    case sf::Keyboard::Comma :
        ret="Comma";break;
    case sf::Keyboard::Period :
        ret="Period";break;
    case sf::Keyboard::Quote :
        ret="Quote";break;
    case sf::Keyboard::Slash :
        ret="Slash";break;
    case sf::Keyboard::BackSlash :
        ret="BackSlash";break;
    case sf::Keyboard::Tilde :
        ret="Tilde";break;
    case sf::Keyboard::Equal :
        ret="Equal";break;
    case sf::Keyboard::Dash :
        ret="Dash";break;
    case sf::Keyboard::Space :
        ret="Space";break;
    case sf::Keyboard::Return :
        ret="Return";break;
    case sf::Keyboard::BackSpace :
        ret="BackSpace";break;
    case sf::Keyboard::Tab :
        ret="Tab";break;
    case sf::Keyboard::PageUp :
        ret="PageUp";break;
    case sf::Keyboard::PageDown :
        ret="PageDown";break;
    case sf::Keyboard::End :
        ret="End";break;
    case sf::Keyboard::Home :
        ret="Home";break;
    case sf::Keyboard::Insert :
        ret="Insert";break;
    case sf::Keyboard::Delete :
        ret="Delete";break;
    case sf::Keyboard::Add :
        ret="Add";break;
    case sf::Keyboard::Subtract :
        ret="Subtract";break;
    case sf::Keyboard::Multiply :
        ret="Multiply";break;
    case sf::Keyboard::Divide :
        ret="Divide";break;
    case sf::Keyboard::Left :
        ret="Left";break;
    case sf::Keyboard::Right :
        ret="Right";break;
    case sf::Keyboard::Up :
        ret="Up";break;
    case sf::Keyboard::Down :
        ret="Down";break;
    case sf::Keyboard::Numpad0 :
        ret="Numpad0";break;
    case sf::Keyboard::Numpad1 :
        ret="Numpad1";break;
    case sf::Keyboard::Numpad2 :
        ret="Numpad2";break;
    case sf::Keyboard::Numpad3 :
        ret="Numpad3";break;
    case sf::Keyboard::Numpad4 :
        ret="Numpad4";break;
    case sf::Keyboard::Numpad5 :
        ret="Numpad5";break;
    case sf::Keyboard::Numpad6 :
        ret="Numpad6";break;
    case sf::Keyboard::Numpad7 :
        ret="Numpad7";break;
    case sf::Keyboard::Numpad8 :
        ret="Numpad8";break;
    case sf::Keyboard::Numpad9 :
        ret="Numpad9";break;
    case sf::Keyboard::F1 :
        ret="F1";break;
    case sf::Keyboard::F2 :
        ret="F2";break;
    case sf::Keyboard::F3 :
        ret="F3";break;
    case sf::Keyboard::F4 :
        ret="F4";break;
    case sf::Keyboard::F5 :
        ret="F5";break;
    case sf::Keyboard::F6 :
        ret="F6";break;
    case sf::Keyboard::F7 :
        ret="F7";break;
    case sf::Keyboard::F8 :
        ret="F8";break;
    case sf::Keyboard::F9 :
        ret="F9";break;
    case sf::Keyboard::F10 :
        ret="F10";break;
    case sf::Keyboard::F11 :
        ret="F11";break;
    case sf::Keyboard::F12 :
        ret="F12";break;
    case sf::Keyboard::F13 :
        ret="F13";break;
    case sf::Keyboard::F14 :
        ret="F14";break;
    case sf::Keyboard::F15 :
        ret="F15";break;
    case sf::Keyboard::Pause :
        ret="Pause";break;
    case sf::Keyboard::KeyCount :
        ret="KeyCount";break;


    default:
        ret="Unknow";break;
        }
    return ret;
}


sf::Keyboard::Key Keys::fromStringToKey(const std::string& k) {
    if (k == "A") return sf::Keyboard::A;
    else if (k == "B") return sf::Keyboard::B;
    else if (k == "C") return sf::Keyboard::C;
    else if (k == "D") return sf::Keyboard::D;
    else if (k == "E") return sf::Keyboard::E;
    else if (k == "F") return sf::Keyboard::F;
    else if (k == "G") return sf::Keyboard::G;
    else if (k == "H") return sf::Keyboard::H;
    else if (k == "I") return sf::Keyboard::I;
    else if (k == "J") return sf::Keyboard::J;
    else if (k == "K") return sf::Keyboard::K;
    else if (k == "L") return sf::Keyboard::L;
    else if (k == "M") return sf::Keyboard::M;
    else if (k == "N") return sf::Keyboard::N;
    else if (k == "O") return sf::Keyboard::O;
    else if (k == "P") return sf::Keyboard::P;
    else if (k == "Q") return sf::Keyboard::Q;
    else if (k == "R") return sf::Keyboard::R;
    else if (k == "S") return sf::Keyboard::S;
    else if (k == "T") return sf::Keyboard::T;
    else if (k == "U") return sf::Keyboard::U;
    else if (k == "V") return sf::Keyboard::V;
    else if (k == "W") return sf::Keyboard::W;
    else if (k == "X") return sf::Keyboard::X;
    else if (k == "Y") return sf::Keyboard::Y;
    else if (k == "Z") return sf::Keyboard::Z;
    else if (k == "Num0") return sf::Keyboard::Num0;
    else if (k == "Num1") return sf::Keyboard::Num1;
    else if (k == "Num2") return sf::Keyboard::Num2;
    else if (k == "Num3") return sf::Keyboard::Num3;
    else if (k == "Num4") return sf::Keyboard::Num4;
    else if (k == "Num5") return sf::Keyboard::Num5;
    else if (k == "Num6") return sf::Keyboard::Num6;
    else if (k == "Num7") return sf::Keyboard::Num7;
    else if (k == "Num8") return sf::Keyboard::Num8;
    else if (k == "Num9") return sf::Keyboard::Num9;
    else if (k == "Escape") return sf::Keyboard::Escape;
    else if (k == "LControl") return sf::Keyboard::LControl;
    else if (k == "LShift") return sf::Keyboard::LShift;
    else if (k == "LAlt") return sf::Keyboard::LAlt;
    else if (k == "LSystem") return sf::Keyboard::LSystem;
    else if (k == "RControl") return sf::Keyboard::RControl;
    else if (k == "RShift") return sf::Keyboard::RShift;
    else if (k == "RAlt") return sf::Keyboard::RAlt;
    else if (k == "RSystem") return sf::Keyboard::RSystem;
    else if (k == "Menu") return sf::Keyboard::Menu;
    else if (k == "LBracket") return sf::Keyboard::LBracket;
    else if (k == "RBracket") return sf::Keyboard::RBracket;
    else if (k == "SemiColon") return sf::Keyboard::SemiColon;
    else if (k == "Comma") return sf::Keyboard::Comma;
    else if (k == "Period") return sf::Keyboard::Period;
    else if (k == "Quote") return sf::Keyboard::Quote;
    else if (k == "Slash") return sf::Keyboard::Slash;
    else if (k == "BackSlash") return sf::Keyboard::BackSlash;
    else if (k == "Tilde") return sf::Keyboard::Tilde;
    else if (k == "Equal") return sf::Keyboard::Equal;
    else if (k == "Dash") return sf::Keyboard::Dash;
    else if (k == "Space") return sf::Keyboard::Space;
    else if (k == "Return") return sf::Keyboard::Return;
    else if (k == "BackSpace") return sf::Keyboard::BackSpace;
    else if (k == "Tab") return sf::Keyboard::Tab;
    else if (k == "PageUp") return sf::Keyboard::PageUp;
    else if (k == "PageDown") return sf::Keyboard::PageDown;
    else if (k == "End") return sf::Keyboard::End;
    else if (k == "Home") return sf::Keyboard::Home;
    else if (k == "Insert") return sf::Keyboard::Insert;
    else if (k == "Delete") return sf::Keyboard::Delete;
    else if (k == "Add") return sf::Keyboard::Add;
    else if (k == "Subtract") return sf::Keyboard::Subtract;
    else if (k == "Multiply") return sf::Keyboard::Multiply;
    else if (k == "Divide") return sf::Keyboard::Divide;
    else if (k == "Left") return sf::Keyboard::Left;
    else if (k == "Right") return sf::Keyboard::Right;
    else if (k == "Up") return sf::Keyboard::Up;
    else if (k == "Down") return sf::Keyboard::Down;
    else if (k == "Numpad0") return sf::Keyboard::Numpad0;
    else if (k == "Numpad1") return sf::Keyboard::Numpad1;
    else if (k == "Numpad2") return sf::Keyboard::Numpad2;
    else if (k == "Numpad3") return sf::Keyboard::Numpad3;
    else if (k == "Numpad4") return sf::Keyboard::Numpad4;
    else if (k == "Numpad5") return sf::Keyboard::Numpad5;
    else if (k == "Numpad6") return sf::Keyboard::Numpad6;
    else if (k == "Numpad7") return sf::Keyboard::Numpad7;
    else if (k == "Numpad8") return sf::Keyboard::Numpad8;
    else if (k == "Numpad9") return sf::Keyboard::Numpad9;
    else if (k == "F1") return sf::Keyboard::F1;
    else if (k == "F2") return sf::Keyboard::F2;
    else if (k == "F3") return sf::Keyboard::F3;
    else if (k == "F4") return sf::Keyboard::F4;
    else if (k == "F5") return sf::Keyboard::F5;
    else if (k == "F6") return sf::Keyboard::F6;
    else if (k == "F7") return sf::Keyboard::F7;
    else if (k == "F8") return sf::Keyboard::F8;
    else if (k == "F9") return sf::Keyboard::F9;
    else if (k == "F10") return sf::Keyboard::F10;
    else if (k == "F11") return sf::Keyboard::F11;
    else if (k == "F12") return sf::Keyboard::F12;
    else if (k == "F13") return sf::Keyboard::F13;
    else if (k == "F14") return sf::Keyboard::F14;
    else if (k == "F15") return sf::Keyboard::F15;
    else if (k == "Pause") return sf::Keyboard::Pause;
    else if (k == "KeyCount") return sf::Keyboard::KeyCount;
    else return sf::Keyboard::Unknown;
}
