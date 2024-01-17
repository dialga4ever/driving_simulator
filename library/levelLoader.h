#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <set>
#include <vector>

using namespace std;
using namespace sf;
#define SIZE_MAP_Y 9
#define SIZE_MAP_X 10
class Level{

    public:
    map<string, Texture> textures;
    pair<string, int> non_osbstacleMap [SIZE_MAP_Y][SIZE_MAP_X];
    vector<Sprite> obstacles;
    vector<String> obstaclesTexture;
    vector<Sprite> non_obstacles;
    Sprite creation;
    int creationTex=0;
    int creationRotation=0;

    bool loaded=false;
    bool rotate=false;
    bool nextTexture=false;
    bool clicked=true;
    bool colissionMode=true;
    bool ChangingMode=false;


    Level();
    Level(string path);


    void load(string path);

    Sprite createObs(int x, int y);

    void loadTextures();

    void loadObstacles();
    void createLevel(RenderWindow *window,String path);

    Sprite placeObject(string image, int x, int y);

    Sprite placeObject(string image, int x, int y, int rotation,float scale);
    Sprite placeObjectFix(string image, int x, int y, int rotation,float scale);        
};



