#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 360), "The Game");
    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.setFillColor(sf::Color::Green);
        window.draw(shape);
        window.display();
    }

    return 0;
}
