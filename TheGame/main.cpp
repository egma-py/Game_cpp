#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#define pi 3.14159

class Level{
private:
    sf::Color FloorColor_ = sf::Color(128, 129, 130);
    sf::RectangleShape Field_;
    std::pair<int, int> WindowSize_;
    float x_, y_;
    float length_, width_;
    std::pair<float, float> spawn_point_;

public:
    Level(std::pair<int, int> WindowSize) {
        this->WindowSize_ = WindowSize;

        this->length_ = (10 * WindowSize.first) / 16;
        this->width_ = (7 * WindowSize.second) / 9;
        this->Field_ = sf::RectangleShape(sf::Vector2f(this->length_, this->width_));
        this->Field_.setFillColor(this->FloorColor_);

        this->x_ = (4 * WindowSize.first) / 16;
        this->y_ = (WindowSize.second) / 9;
        this->Field_.move(this->x_, this->y_);
    }

    sf::RectangleShape toDraw() {
        return this->Field_;
    }

    float get_x() {
        return this->x_;
    }

    float get_y() {
        return this->y_;
    }

    std::pair<int, int> get_size() {
        std::pair<float, float> ans;
        ans.first = this->length_;
        ans.second = this->width_;
        return ans;
    }
};


class Enemy {
private:
    sf::CircleShape obj_;
    float x_, y_, radius_;
    float phi_ = 0;
    float alpha_ = pi / 9;
    float distance_ = 100;
public:
        Enemy(std::pair<int, int> WindowSize) {
        this->x_ = WindowSize.first / 2;
        this->y_ = WindowSize.second / 2;
        this->radius_ = WindowSize.first / 90;
        this->obj_ = sf::CircleShape(this->radius_);
        this->obj_.setFillColor(sf::Color::Green);
        this->obj_.move(this->x_, this-> y_);
    }

    float get_x() {
        return this->x_;
    }

    float get_y() {
        return this->y_;
    }

    float get_r() {
        return this->radius_;
    }

    float get_d() {
        return this->distance_;
    }

    float get_phi() {
        return this->phi_;
    }

    float get_alpha() {
        return this->alpha_;
    }

    sf::ConvexShape toDrawSight() {
        sf::ConvexShape ans;
        ans.setFillColor(sf::Color::Blue);
        ans.setPointCount(13);
        for (int i = 0; i < 12; ++i) {
            sf::Vector2f point;
            float d = this->distance_;
            float phi = this->phi_;
            float alpha = this->alpha_;
            point = sf::Vector2f(d * std::cos(phi + alpha - (i*2*alpha) / 11), d * std::sin(phi + alpha - (i*2*alpha) / 11));
            ans.setPoint(i, point);
        }
        ans.setPoint(12, sf::Vector2f(0, 0));
        float center_x = this->x_ + this->radius_;
        float center_y = this->y_ + this->radius_;
        ans.move(center_x, center_y);
        return ans;
    }

    sf::CircleShape toDraw() {
        return this->obj_;
    }

    void pluss() {
        this->phi_ += pi / 20;
    }


    void movee() {
        obj_.move(1,1);
        this->x_ += 1;
        this->y_ += 1;
    }
};

class Hero {
private:
    int hp_ = 5;
    int speed = 3;

    int acceleration_time_;

    float x_, y_;

    float radius_;

    std::pair<int, int> hpbar_size_;


    sf::CircleShape obj_;
public:
    Hero(std::pair<int, int> WindowSize) {
        this->x_ = WindowSize.first / 2;
        this->y_ = WindowSize.second / 2;
        this->radius_ = WindowSize.first / 90;
        this->obj_ = sf::CircleShape(this->radius_);
        this->obj_.setFillColor(sf::Color::Red);
        this->obj_.move(this->x_, this-> y_);
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

    void move_hero(Level level) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (level.get_y() < this->y_ - this->speed) {
                this->move_on_dir('W');
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (level.get_x() < this->x_ - this->speed) {
                this->move_on_dir('A');
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (level.get_y() + level.get_size().second > this->y_ + this->speed + 2 * this->radius_) {
                this->move_on_dir('S');
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (level.get_x() + level.get_size().first > this->x_ + this->speed + 2 * this->radius_) {
                this->move_on_dir('D');
            }
        }
    }

    void move_on_dir(char key) {
        if (key == 'W') {
            this->obj_.move(0, -this->speed);
            this->y_ -= this->speed;
        }
        else if (key == 'A') {
            this->obj_.move(-this->speed, 0);
            this->x_ -= this->speed;
        }
        else if (key == 'S') {
            this->obj_.move(0, this->speed);
            this->y_ += this->speed;
        }
        else if (key == 'D') {
            this->obj_.move(this->speed, 0);
            this->x_ += this->speed;
        }
    }

    bool isDead() {
        return this->hp_ <= 0;
    }

    void GetDamage() {
        --this->hp_;
    }

    bool isSpotted(Enemy enemy) {
        float delta_x = this->x_ - enemy.get_x();
        float delta_y = this->y_ - enemy.get_y();

        float r = sqrt(delta_x*delta_x + delta_y*delta_y);

        if (delta_x == 0 || delta_y == 0) {
            if (r < enemy.get_d()) {
                return true;
            }
            return false;
        }

        if (delta_y > 0) {
            if (acos(delta_x / r) > enemy.get_phi() - enemy.get_alpha() && acos(delta_x / r) > enemy.get_phi() + enemy.get_alpha()) {
                if (r < enemy.get_d()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if (delta_y < 0) {
            if (acos(-delta_x / r) - pi > enemy.get_phi() - enemy.get_alpha() && acos(-delta_x / r) - pi > enemy.get_phi() + enemy.get_alpha()) {
                if (r < enemy.get_d()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }

        return false;
    }
};


int main()
{
    std::pair<int, int> WindowSize;
    WindowSize.first = 1080;
    WindowSize.second = 720;

    int FPS = 30;

    Level level(WindowSize);
    Enemy enemy(WindowSize);
    Hero hero(WindowSize);

    sf::RenderWindow window(sf::VideoMode(WindowSize.first, WindowSize.second), "The Game");
    window.setFramerateLimit(FPS);

    while (window.isOpen())
    {
        sf::Event event;

        //enemy.pluss();
        //enemy.movee();

        if (hero.isSpotted(enemy)) {
            std::cout << "warn" << std::endl;
        }

        while (window.pollEvent(event)){


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
                    hero.move_hero(level);

                default:
                    break;

            }
        }

        window.clear();
        window.draw(level.toDraw());
        window.draw(hero.toDrawhp());
        window.draw(enemy.toDrawSight());
        window.draw(enemy.toDraw());
        window.draw(hero.toDraw());
        window.display();
    }

    return 0;
}
