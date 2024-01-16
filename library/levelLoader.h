#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <set>
#include <vector>

using namespace std;
using namespace sf;

class Level{

    public:
    map<string, Texture> textures;
    vector<Sprite> obstacles;
    vector<Sprite> non_obstacles;
    
    Level();
    Level(string path);

    void load(string path);

    Sprite createObs(int x, int y);

    void loadTextures();

    void loadObstacles();

    Sprite placeObject(string image, int x, int y);

    Sprite placeObject(string image, int x, int y, int rotation);
};



