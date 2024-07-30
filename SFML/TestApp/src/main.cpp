#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

enum struct ResultCodes : int
{
    Ok = 0,
    Error = 1
};


int SfmlWindow()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

int main(int argc, char *argv[])
{
    ResultCodes result = ResultCodes::Ok;

    printf("Test\n");

    SfmlWindow();
    
    return static_cast<int>(result);    
}
