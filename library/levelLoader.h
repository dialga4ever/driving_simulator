#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

class Level{

    public:


    
    Level();
    Level(string path);

    void load(string path);
};
