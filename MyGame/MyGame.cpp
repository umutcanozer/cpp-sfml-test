#include "SFML/Graphics.hpp"

int main()
{
    int w = 600; int h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");
    sf::Event e;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
