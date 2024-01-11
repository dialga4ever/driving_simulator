#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <set>
#include <vector>

using namespace std;
using namespace sf;

class Level{

    public:
    vector<Sprite> obs;

    
    Level();
    Level(string path);

    void load(string path);

    Sprite createObs(int x, int y);
};
