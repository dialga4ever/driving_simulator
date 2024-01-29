#include "textureUtility.h"
#include "choixLevel.h"
#include <bits/stdc++.h>  
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>


using namespace std;
using namespace sf;




ChoixMap::ChoixMap(sf::RenderWindow *window, sf::Font font){
    filesystem::path path1{"./level"};
    
    for (auto const& dir_entry : std::filesystem::directory_iterator{ path1 }){
        auto path1 = dir_entry.path();
        createButton(path1.filename(), {100,100},window,font);
    }
    loaded = true;
}

void ChoixMap::createButton(string nom, Vector2f pos, RenderWindow* window, Font font){
    Button self;
    self.choix_map_texture.loadFromFile("src/other/bouton.png");
    self.choix_map_sprite.setTexture(self.choix_map_texture);
    self.choix_map_sprite.setPosition(pos);
    self.choix_map_sprite.scale({1,0.5});
    centerOrigin(&self.choix_map_sprite);
    self.choix_map_text.setFont(font); 
    self.choix_map_text.setString(nom);
    self.choix_map_text.setCharacterSize(16); 
    self.choix_map_text.setFillColor(Color::Black);
    self.choix_map_text.setStyle(Text::Bold);
    self.choix_map_text.setPosition(self.choix_map_sprite.getPosition());
    centerTextOrigin(&self.choix_map_text);
    list_map.insert({nom, self});
}