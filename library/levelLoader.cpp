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
}




void loadObstacles(map<string, Texture> *textures, vector<Sprite> *obstacles){
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