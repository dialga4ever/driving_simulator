#include <SFML/Graphics.hpp>
#include "textureUtility.h"
#include "levelLoader.h"


using namespace std;
using namespace sf;

Level::Level(){
    
    obs.push_back(createObs(10, 10));
    obs.push_back(createObs(150, 500));
    return;
}
Level::Level(string path){
    return;
}

void load(string path){
    return;
}

Sprite Level::createObs(int pos_x, int pos_y){
    Sprite obs1;
    Texture carTexture;
    spriteLoadFromFilePos(&obs1,&carTexture,"./src/texture/voiture_orange.jpg", pos_x, pos_y);
    centerOrigin(&obs1);
    return obs1;
}




int main()
{
    RenderWindow window(VideoMode(1000, 1000), "Driving Simulator", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    Level niv = Level();
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();

        for(auto i : niv.obs){
            window.draw(i);
        }
        window.display();
    }
}