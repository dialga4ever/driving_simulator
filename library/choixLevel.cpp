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




ChoixMap::ChoixMap(sf::Font font_){
    filesystem::path path1{"./level"};
    int x = 200;
    int y = 100;

    font = font_;
    texture.loadFromFile("src/other/bouton.png");

    
    for (auto const& dir_entry : std::filesystem::directory_iterator{ path1 }){
        auto path1 = dir_entry.path();

        createButton(path1.filename(), {x,y});

        y += 100;
        printf("6 %d %d\n", x, y);

            printf("6\n");
    }
    loaded = true;
}



void ChoixMap::mettre_a_jour(){
    ChoixMap newChoix(font);
    printf("1\n");
    *this = newChoix;
    printf("2\n");
}

void ChoixMap::createButton(string nom, Vector2f pos){
    Button self;
    self.choix_map_sprite.setTexture(texture);
    self.choix_map_sprite.setPosition(pos);
    self.choix_map_sprite.scale({0.5,0.5});
    centerOrigin(&self.choix_map_sprite);
    self.choix_map_text.setFont(font);
    printf("%s\n",nom.c_str());
    self.choix_map_text.setString((sf::String)nom);
    self.choix_map_text.setCharacterSize(16);
    self.choix_map_text.setFillColor(Color::Black);
    self.choix_map_text.setStyle(Text::Bold);
    self.choix_map_text.setPosition(self.choix_map_sprite.getPosition());
    centerTextOrigin(&self.choix_map_text);
    list_map.insert({nom, self});
}