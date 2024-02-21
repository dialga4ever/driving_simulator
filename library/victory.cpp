#include "victory.h"
#include "textureUtility.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>





Victory::Victory(int window_x_, int window_y_, sf::Font font_){
    window_x = (float) window_x_;
    window_y = (float) window_y_;
    font = font_;
    loaded = false;

    
}


void Victory::load(std::string map_name){
    createItem("étoile1", " ", "src/other/star_on.png", {window_x/2-150, window_y/2});
    createItem("étoile2", " ", "src/other/star_on.png", {window_x/2, window_y/2});
    createItem("étoile3", " ", "src/other/star_on.png", {window_x/2+150, window_y/2});

    createText("map name", map_name, {window_x/2, window_y/1.5});
}

void Victory::createItem(std::string nom, std::string text, std::string texture_path, sf::Vector2f pos){
    Item self;

    sf::Texture texture;
    texture.loadFromFile("../" + texture_path);

    self.sprite.setTexture(texture);
    textures.push_back(texture);
    self.sprite.setPosition(pos);
    self.sprite.scale({1,1});
    centerOrigin(&self.sprite);
    self.text.setFont(font); 
    self.text.setString(text);
    self.text.setCharacterSize(16); 
    self.text.setFillColor(sf::Color::Black);
    self.text.setStyle(sf::Text::Bold);
    self.text.setPosition(self.sprite.getPosition());
    centerTextOrigin(&self.text);
    items.insert({nom, self});
}

void Victory::createText(std::string nom, std::string str, sf::Vector2f pos){
    sf::Text text;
    text.setFont(font); 
    text.setString(nom);
    text.setCharacterSize(16); 
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(pos);
    centerTextOrigin(&text);
    texts.insert({nom, text});
}