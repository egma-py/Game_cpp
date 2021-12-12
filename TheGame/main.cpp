#include <SFML/Graphics.hpp>
#include <iostream>

class Hero {
private:

public:

};

class Enemy {
private:

public:

};

class Level{
private:
    sf::Color FloorColor_ = sf::Color(128, 129, 130);
    sf::RectangleShape Field_;
    std::pair<int, int> WindowSize_;
public:
    Level(std::pair<int, int> WindowSize) {
        this->WindowSize_ = WindowSize;

        float length = (10 * WindowSize.first) / 16;
        float width = (7 * WindowSize.second) / 9;
        this->Field_ = sf::RectangleShape(sf::Vector2f(length, width));
        this->Field_.setFillColor(this->FloorColor_);

        float x = (3 * WindowSize.first) / 16;
        float y = (WindowSize.second) / 9;
        this->Field_.move(x, y);
    }

    sf::RectangleShape Draw() {
        return this->Field_;
    }
};

int main()
{
    std::pair<int, int> WindowSize;
    WindowSize.first = 1080;
    WindowSize.second = 720;

    Level level(WindowSize);

    sf::RenderWindow window(sf::VideoMode(WindowSize.first, WindowSize.second), "The Game");
    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    std::cout << '(' << event.mouseButton.x << ", " << event.mouseButton.y << ')' << ' ';

                default:
                    break;

            }
        }

        window.clear();
        window.draw(level.Draw());
        window.draw(shape);
        window.display();
    }

    return 0;
}
