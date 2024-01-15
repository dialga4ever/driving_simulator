#include <SFML/Graphics.hpp>
#include "textureUtility.h"
#include "levelLoader.h"


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


void loadTextures(map<string, Texture> *textures){
    Texture t;

    if (!t.loadFromFile("src/texture/cursor.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("cursor.png", t));
    if (!t.loadFromFile("src/texture/test.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("test.jpg", t));
    if (!t.loadFromFile("src/texture/voiture_orange.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("voiture_orange.jpg", t));
    if (!t.loadFromFile("src/texture/brique.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("brique.jpg", t));
    if (!t.loadFromFile("src/texture/route1.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("route1.bmp", t));
    if (!t.loadFromFile("src/texture/route2.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("route2.bmp", t));
    if (!t.loadFromFile("src/texture/route_slow1.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("route_slow1.bmp", t));
    if (!t.loadFromFile("src/texture/route_slow2.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("route_slow2.bmp", t));
    if (!t.loadFromFile("src/texture/route_egout.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("route_egout.bmp", t));
    if (!t.loadFromFile("src/texture/route_virage1.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("route_virage1.bmp", t));
    if (!t.loadFromFile("src/texture/route_virage2.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures->insert(pair<string, Texture>("route_virage2.bmp", t));
}




void loadObstacles(map<string, Texture> *textures, vector<Sprite> *obstacles, vector<Sprite> *non_obstacles){
    Sprite obs1;
    obs1.setTexture(textures->at("voiture_orange.jpg"));
    obs1.setPosition(200, 200);
    obs1.scale(0.1, 0.1);
    centerOrigin(&obs1);
    obstacles->push_back(obs1);

    Sprite obs2;
    obs2.setTexture(textures->at("brique.jpg"));
    obs2.setPosition(300, 200);
    obs2.scale(0.1, 0.1);
    centerOrigin(&obs2);
    obstacles->push_back(obs2);

//1 | 1
    Sprite obs3;
    obs3.setTexture(textures->at("route1.bmp"));
    obs3.setPosition(400, 200);
    centerOrigin(&obs3);
    non_obstacles->push_back(obs3);

//2 | 1
    Sprite obs4;
    obs4.setTexture(textures->at("route1.bmp"));
    obs4.setPosition(464, 200);
    obs4.setRotation(180);
    centerOrigin(&obs4);
    non_obstacles->push_back(obs4);

//1 | 2
    obs3.setTexture(textures->at("route1.bmp"));
    obs3.setPosition(400, 264);
    centerOrigin(&obs3);
    non_obstacles->push_back(obs3);

//2 | 2
    obs4.setTexture(textures->at("route1.bmp"));
    obs4.setPosition(464, 264);
    obs4.setRotation(180);
    centerOrigin(&obs4);
    non_obstacles->push_back(obs4);

//1 | 3
    obs3.setTexture(textures->at("route1.bmp"));
    obs3.setPosition(400, 328);
    centerOrigin(&obs3);
    non_obstacles->push_back(obs3);

//2 | 3
    obs4.setTexture(textures->at("route1.bmp"));
    obs4.setPosition(464, 328);
    obs4.setRotation(180);
    centerOrigin(&obs4);
    non_obstacles->push_back(obs4);

//1 | 4
    obs3.setTexture(textures->at("route_egout.bmp"));
    obs3.setPosition(400, 392);
    centerOrigin(&obs3);
    non_obstacles->push_back(obs3);

//2 | 4
    obs4.setTexture(textures->at("route1.bmp"));
    obs4.setPosition(464, 392);
    obs4.setRotation(180);
    centerOrigin(&obs4);
    non_obstacles->push_back(obs4);

//1 | 5
    obs3.setTexture(textures->at("route1.bmp"));
    obs3.setPosition(400, 456);
    centerOrigin(&obs3);
    non_obstacles->push_back(obs3);

//2 | 5
    obs4.setTexture(textures->at("route1.bmp"));
    obs4.setPosition(464, 456);
    obs4.setRotation(180);
    centerOrigin(&obs4);
    non_obstacles->push_back(obs4);

//1 | 6
    obs3.setTexture(textures->at("route_virage2.bmp"));
    obs3.setPosition(400, 530);
    centerOrigin(&obs3);
    non_obstacles->push_back(obs3);

//2 | 6
    obs4.setTexture(textures->at("route_virage1.bmp"));
    obs4.setPosition(464, 530);
    obs4.setRotation(0);
    centerOrigin(&obs4);
    non_obstacles->push_back(obs4);
}



/*int main()
{
    RenderWindow window(VideoMode(1000, 1000), "Driving Simulator", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);


    Level niv = Level();

    loadTextures(&niv.textures);

    loadObstacles(&niv.textures, &niv.obstacles);


    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        for(auto i : niv.obstacles){
            window.draw(i);
        }
        window.display();
    }
}*/