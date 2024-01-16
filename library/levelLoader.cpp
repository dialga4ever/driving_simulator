#include <SFML/Graphics.hpp>
#include "textureUtility.h"
#include "levelLoader.h"

#define OFFSET 64
#define SIZE_MAP_Y 9
#define SIZE_MAP_X 10

using namespace std;
using namespace sf;

Level::Level(){
    return;
}
Level::Level(string path){
    return;
}

void load(string path){
    return;
}


void Level::loadTextures(){
    Texture t;

    if (!t.loadFromFile("src/texture/cursor.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("cursor.png", t));
    if (!t.loadFromFile("src/texture/test.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("test.jpg", t));
    if (!t.loadFromFile("src/texture/voiture_orange.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("voiture_orange.jpg", t));
    if (!t.loadFromFile("src/texture/brique.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("brique.jpg", t));
    if (!t.loadFromFile("src/texture/route1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route1.png", t));
    if (!t.loadFromFile("src/texture/route2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route2.png", t));
    if (!t.loadFromFile("src/texture/route_slow1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_slow1.png", t));
    if (!t.loadFromFile("src/texture/route_slow2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_slow2.png", t));
    if (!t.loadFromFile("src/texture/route_egout.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_egout.png", t));
    if (!t.loadFromFile("src/texture/route_virage_exte.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_virage_exte.png", t));
    if (!t.loadFromFile("src/texture/route_virage_inte.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_virage_inte.png", t));
    if (!t.loadFromFile("src/texture/trotoire.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("trotoire.png", t));
    if (!t.loadFromFile("src/texture/route_parking_place.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_parking_place.png", t));
    if (!t.loadFromFile("src/texture/route_sans_bord.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_sans_bord.png", t));
    if (!t.loadFromFile("src/texture/route_bord1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_bord1.png", t));
    if (!t.loadFromFile("src/texture/route_bord2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_bord2.png", t));
    if (!t.loadFromFile("src/texture/route_bord3.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_bord3.png", t));
    if (!t.loadFromFile("src/texture/buisson_coin.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("buisson_coin.png", t));
    if (!t.loadFromFile("src/texture/buisson_cote.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("buisson_cote.png", t));
    if (!t.loadFromFile("src/texture/route_croisement1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_croisement1.png", t));
    if (!t.loadFromFile("src/texture/route_croisement2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_croisement2.png", t));
    if (!t.loadFromFile("src/texture/ventilo.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("ventilo.bmp", t));
    if (!t.loadFromFile("src/texture/phare.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("phare.png", t));
}



void Level::loadObstacles(){
    printf("1\n");
    pair<string, int> map [SIZE_MAP_Y][SIZE_MAP_X] = 
    {{{"trotoire.png",0},   {"trotoire.png",90},            {"trotoire.png",180},           {"trotoire.png",0},     {"trotoire.png",270},           {"trotoire.png",90},            {"trotoire.png",180},       {"trotoire.png",0},             {"trotoire.png",180},           {"trotoire.png",270}},
    {{"trotoire.png",270},  {"route_virage_exte.png",0},    {"route1.png",90},              {"route_egout.png",90}, {"route1.png",90},              {"route1.png",90},              {"route1.png",90},          {"route_egout.png",90},         {"route1.png",90},              {"route_virage_exte.png",90}},
    {{"trotoire.png",0},    {"route1.png",0},               {"route_virage_inte.png",0},    {"route1.png",270},     {"route1.png",270},             {"route_croisement2.png",270},  {"route_sans_bord.png",90}, {"route_croisement1.png",270},  {"route_virage_inte.png",90},   {"route1.png",180}},
    {{"trotoire.png",90},   {"route1.png",0},               {"route1.png",180},             {"buisson_coin.png",0}, {"buisson_coin.png",90},        {"route_bord2.png",180},        {"route_bord3.png",180},    {"route_bord1.png",180},        {"route1.png",0},               {"route_egout.png",180}},
    {{"trotoire.png",0},    {"route_egout.png",0},          {"route1.png",180},             {"buisson_coin.png",270},{"buisson_coin.png",180},      {"trotoire.png",180},           {"trotoire.png",0},         {"trotoire.png",90},            {"route1.png",0},               {"route1.png",180}},
    {{"trotoire.png",270},  {"route1.png",0},               {"route1.png",180},             {"trotoire.png",0},     {"route_bord1.png",0},          {"route_bord3.png",0},          {"route_bord3.png",0},      {"route_bord2.png",0},          {"route1.png",0},               {"route1.png",180}},
    {{"trotoire.png",0},    {"route1.png",0},               {"route_virage_inte.png",270},  {"route1.png",90},      {"route_croisement1.png",90},   {"route_sans_bord.png",90},     {"route_sans_bord.png",90}, {"route_croisement2.png",90},   {"route_virage_inte.png",180},  {"route1.png",180}},
    {{"trotoire.png",180},  {"route1.png",0},               {"route_virage_inte.png",0},    {"route1.png",270},     {"route_croisement2.png",270},  {"route_sans_bord.png",90},     {"route_sans_bord.png",90}, {"route_croisement1.png",270},  {"route_egout.png",270},        {"route_virage_exte.png",180}},
    {{"trotoire.png",270},  {"route_egout.png",0},          {"route1.png",180},             {"trotoire.png",90},    {"route_bord2.png",180},        {"route_bord3.png",180},        {"route_bord3.png",180},    {"route_bord1.png",180},        {"trotoire.png",180},           {"trotoire.png",180}}
    };



    for(int i = 0; i < SIZE_MAP_Y; i++){
        for(int j = 0; j < SIZE_MAP_X; j++){
            printf("i %d, j %d\n\n", i, j);
            non_obstacles.push_back(placeObject(map[i][j].first, j, i, map[i][j].second));
        }
    }

    obstacles.push_back(placeObject("ventilo.bmp", 4, 4, 90));
    
}

Sprite Level::placeObject(string image, int x, int y){
    Sprite obs;
    obs.setTexture(textures.at(image));
    obs.setPosition(x*OFFSET, y*OFFSET);
    centerOrigin(&obs);
    return obs;
}

Sprite Level::placeObject(string image, int x, int y, int rotation){
    Sprite obs;
    obs.setTexture(textures.at(image));
    obs.setRotation(rotation);
    obs.setPosition(x*OFFSET, y*OFFSET);
    centerOrigin(&obs);
    return obs;
}