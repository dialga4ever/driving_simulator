#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "car.h"

using namespace std;
using namespace sf;

#define PI 3.14159265

int main()
{
    RenderWindow window(VideoMode(1500, 2000), "Driving Simulator");
    window.setVerticalSyncEnabled(true);


    Car car = Car(500, 500);// Création de la voiture

    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            Vector2u w_size = window.getSize();
            unsigned int w_width = w_size.x;
            unsigned int w_height = w_size.y;

            
            if (event.type == Event::Closed)
                window.close();
            
            if (event.type == Event::MouseButtonPressed)
                window.setSize(Vector2u(w_width+10, w_height+10));

            car.move();
        }
        car.deceleration();
        car.deplacement();

        window.clear();
        window.draw(car.rectangle);
        window.display();
    }

    return 0;
}
