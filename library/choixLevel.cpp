#include "textureUtility.h"
#include "choixLevel.h"
#include <bits/stdc++.h>  
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <set>


using namespace std;
using namespace sf;




ChoixMap::ChoixMap(int window_x_, int window_y_, sf::Font font_){
    loadTexture("étoile", "src/other/star_on.png");
    loadTexture("star_off", "src/other/star_off.png");

    filesystem::path path1{"./level"};
    window_x = (float)window_x_;
    window_y = (float)window_y_;

    int number_of_map = 0;
    for (auto const& dir_entry : std::filesystem::directory_iterator{ path1 }){
        number_of_map++;
    }
    float y_add = window_y/number_of_map;

    float y = y_add/2;
    font = font_;
    texture.loadFromFile("src/other/bouton_map.png");


    

    const auto& dir_entry = std::filesystem::directory_iterator{ path1 };

    set<std::filesystem::path> sorted_by_name;

    for (auto &entry : std::filesystem::directory_iterator(path1))
        sorted_by_name.insert(entry.path());
        
    for (auto &dir_entry : sorted_by_name) {
        printf("%s\n",dir_entry.c_str());
        auto path1 = dir_entry;

        createButton(path1.filename(), {window_x/2,y});

        std::filesystem::path path = std::filesystem::path("level") / path1.filename() / "NB_POINT.txt";
        int nb_points=0;
        
        std::ifstream file(path);
        
        file >> nb_points;
        file.close();
        printf("%d\n",nb_points);
        if(nb_points>100){
            createItem("étoile1" + std::string(path1.filename()), &textures.at("étoile"), {window_x-150, y});
            if(nb_points>=250){
                createItem("étoile2" + std::string(path1.filename()), &textures.at("étoile"), {window_x-200, y});
                if(nb_points>=500){
                    createItem("étoile3" + std::string(path1.filename()), &textures.at("étoile"), {window_x-250, y});
                }else{
                    createItem("étoile3" + std::string(path1.filename()), &textures.at("star_off"), {window_x-250, y});
                }
            }else{
                createItem("étoile2" + std::string(path1.filename()), &textures.at("star_off"), {window_x-200, y});
                createItem("étoile3" + std::string(path1.filename()), &textures.at("star_off"), {window_x-250, y});
            }
        }else{
            createItem("étoile1" + std::string(path1.filename()), &textures.at("star_off"), {window_x-150, y});
            createItem("étoile2" + std::string(path1.filename()), &textures.at("star_off"), {window_x-200, y});
            createItem("étoile3" + std::string(path1.filename()), &textures.at("star_off"), {window_x-250, y});
        }

        y += y_add;
    }
}

void ChoixMap::updateStar(int window_x_, int window_y_){
    //delete all star
    items.clear();
    //add all star

    filesystem::path path1{"./level"};
    window_x = (float)window_x_;
    window_y = (float)window_y_;
    int number_of_map = 0;
    for (auto const& dir_entry : std::filesystem::directory_iterator{ path1 }){
        number_of_map++;
    }
    float y_add = window_y/number_of_map;

    float y = y_add/2;
    const auto& dir_entry = std::filesystem::directory_iterator{ path1 };

    set<std::filesystem::path> sorted_by_name;

    for (auto &entry : std::filesystem::directory_iterator(path1))
        sorted_by_name.insert(entry.path());
        
    for (auto &dir_entry : sorted_by_name) {
        auto path1 = dir_entry;
        std::filesystem::path path = std::filesystem::path("level") / path1.filename() / "NB_POINT.txt";
        int nb_points=0;
        
        std::ifstream file(path);
        file >> nb_points;
        if(nb_points>100){
            createItem("étoile1" + std::string(path1.filename()), &textures.at("étoile"), {window_x-150, y});
            if(nb_points>=250){
                createItem("étoile2" + std::string(path1.filename()), &textures.at("étoile"), {window_x-200, y});
                if(nb_points>=500){
                    createItem("étoile3" + std::string(path1.filename()), &textures.at("étoile"), {window_x-250, y});
                }else{
                    createItem("étoile3" + std::string(path1.filename()), &textures.at("star_off"), {window_x-250, y});
                }
            }else{
                createItem("étoile2" + std::string(path1.filename()), &textures.at("star_off"), {window_x-200, y});
                createItem("étoile3" + std::string(path1.filename()), &textures.at("star_off"), {window_x-250, y});
            }
        }else{
            createItem("étoile1" + std::string(path1.filename()), &textures.at("star_off"), {window_x-150, y});
            createItem("étoile2" + std::string(path1.filename()), &textures.at("star_off"), {window_x-200, y});
            createItem("étoile3" + std::string(path1.filename()), &textures.at("star_off"), {window_x-250, y});
        }
        y += y_add;
    }
}

void ChoixMap::mettre_a_jour(){
    ChoixMap newChoix(window_x, window_y, font);
    *this = newChoix;
}

void ChoixMap::createButton(string nom, Vector2f pos){
    Button self;
    self.choix_map_sprite.setTexture(texture);
    self.choix_map_sprite.setPosition(pos);
    self.choix_map_sprite.scale({1,0.5});
    centerOrigin(&self.choix_map_sprite);
    self.choix_map_text.setFont(font);
    self.choix_map_text.setString((sf::String)nom);
    self.choix_map_text.setCharacterSize(16);
    self.choix_map_text.setFillColor(Color::Black);
    self.choix_map_text.setStyle(Text::Bold);
    self.choix_map_text.setPosition(100, self.choix_map_sprite.getPosition().y);
    centerTextOrigin(&self.choix_map_text);
    list_map.insert({nom, self});
}

void ChoixMap::loadTexture(std::string nom, std::string texture_path){
    sf::Texture texture;
    texture.loadFromFile(texture_path);
    textures[nom] = texture;
}

void ChoixMap::createItem(std::string nom, sf::Texture* texture, sf::Vector2f pos){
    Item self;

    self.sprite.setTexture(*texture);
    self.sprite.setPosition(pos);
    self.sprite.scale({1, 1});
    centerOrigin(&self.sprite);
    items.insert({nom, self});
}