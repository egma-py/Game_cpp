#include <SFML/Graphics.hpp>
#include <iostream>

class Hero {
private:
    int hp_ = 5;

    float x,y;

    std::pair<int, int> hpbar_size_;


    sf::CircleShape obj_;
public:
    Hero(std::pair<int, int> WindowSize) {
        this-> x = WindowSize.first / 2;
        this-> y = WindowSize.second / 2;
        this->obj_ = sf::CircleShape(WindowSize.first / 90);
        this->obj_.setFillColor(sf::Color::Red);
        this->obj_.move(this->x, this-> y);
        this->hpbar_size_.first = WindowSize.first / 50;
        this->hpbar_size_.second = WindowSize.second / 50;
    }

    sf::CircleShape toDraw() {
        return this->obj_;
    }

    sf::RectangleShape toDrawhp() {
        sf::RectangleShape hpbar = sf::RectangleShape(sf::Vector2f(this->hp_ * this->hpbar_size_.first, this->hpbar_size_.second));
        if (this->hp_ == 5 || this->hp_ == 4) {
            hpbar.setFillColor(sf::Color::Green);
        }
        else if (this->hp_ == 2 || this->hp_ == 3) {
            hpbar.setFillColor(sf::Color::Yellow);
        }
        else if (this->hp_ == 1) {
            hpbar.setFillColor(sf::Color::Red);
        }
        hpbar.move(this->hpbar_size_.first, 50 * this->hpbar_size_.second / 9);
        return hpbar;
    }

    void moveobj(char key) {
        if (key == 'W') {
            this->obj_.move(0, -5);
            this->y -= 5;
        }
        else if (key == 'A') {
            this->obj_.move(-5, 0);
            this->x -= 5;
        }
        else if (key == 'S') {
            this->obj_.move(0, 5);
            this->y += 5;
        }
        else if (key == 'D') {
            this->obj_.move(5, 0);
            this->x += 5;
        }
    }

    bool isDead() {
        return this->hp_ <= 0;
    }

    void GetDamage() {
        --this->hp_;
    }
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

        float x = (4 * WindowSize.first) / 16;
        float y = (WindowSize.second) / 9;
        this->Field_.move(x, y);
    }

    sf::RectangleShape toDraw() {
        return this->Field_;
    }
};

int main()
{
    std::pair<int, int> WindowSize;
    WindowSize.first = 1080;
    WindowSize.second = 720;

    Level level(WindowSize);
    Hero hero(WindowSize);

    sf::RenderWindow window(sf::VideoMode(WindowSize.first, WindowSize.second), "The Game");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (hero.isDead()) {
                window.close();
            }

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    std::cout << '(' << event.mouseButton.x << ", " << event.mouseButton.y << ')' << std::endl;
                    hero.GetDamage();

                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        hero.moveobj('W');
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        hero.moveobj('A');
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        hero.moveobj('S');
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        hero.moveobj('D');
                    }

                default:
                    break;

            }
        }

        window.clear();
        window.draw(level.toDraw());
        window.draw(hero.toDraw());
        window.draw(hero.toDrawhp());
        window.display();
    }

    return 0;
}
