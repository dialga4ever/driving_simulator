#include "victory.h"
#include "textureUtility.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>
#include <fstream>
#include <iostream>
#include <filesystem>





Victory::Victory(int window_x_, int window_y_, sf::Font font_){
    window_x = (float) window_x_;
    window_y = (float) window_y_;
    font = font_;
    loaded = false;

    
}


void Victory::load(std::string map_name, int nb_points,float time){
    loadTexture("étoile", "src/other/star_on.png");
    loadTexture("bouton", "src/other/touche.png");
    loadTexture("ombre", "src/other/noir.png");
    

    createItem("ombre", " ", &textures.at("ombre"), {window_x/2, window_y/2}, 5, 5);
    items.at("ombre").sprite.setColor(sf::Color(255, 255, 255, 100));

    
    nb_points = nb_points - (int)time;
    if(nb_points>100){
        createItem("étoile1", " ", &textures.at("étoile"), {window_x/2-150, window_y/3});
        if(nb_points>=250){
            createItem("étoile2", " ", &textures.at("étoile"), {window_x/2, (window_y/3)-30});
            if(nb_points>=450){
                createItem("étoile3", " ", &textures.at("étoile"), {window_x/2+150, window_y/3});
            }
        }
    }

    createItem("rejouer", "Retry", &textures.at("bouton"), {window_x/2, window_y/2+50}, 1, 0.5);
    createItem("menu", "Menu", &textures.at("bouton"), {window_x/2, (window_y/2)+150}, 1, 0.5);
    
    
    
    createText("map name", map_name, {window_x/2, window_y/3+60});
    createText("points", std::to_string(nb_points), {window_x/2, window_y/3+100});

    //if nb_points > last save in NB_POINT.txt (folder location : level/map_name/)
    //save nb_points in NB_POINT.txt

    std::string path = "level/"+map_name+"/NB_POINT.txt";
    std::ofstream file(path);
    if(file){
        //check if the file is empty
        file.seekp(0, std::ios::end);
        if(file.tellp() == 0){
            file << nb_points;
        }else{
            int last_points;
            std::ifstream file(path);
            file >> last_points;
            if(nb_points > last_points){
                file.close();
                std::ofstream file(path);
                file << nb_points;
            }
        }
    }
    file.close();
    loaded = true;




}

void Victory::loadTexture(std::string nom, std::string texture_path){
    sf::Texture texture;
    texture.loadFromFile(texture_path);
    textures[nom] = texture;
}

void Victory::createItem(std::string nom, std::string text, sf::Texture* texture, sf::Vector2f pos, float scale_x, float scale_y){
    Item self;

    self.sprite.setTexture(*texture);
    self.sprite.setPosition(pos);
    self.sprite.scale({scale_x, scale_y});
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
    text.setString(str);
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(pos);
    centerTextOrigin(&text);
    texts.insert({nom, text});
}