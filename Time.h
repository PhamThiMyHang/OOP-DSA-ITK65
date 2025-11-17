#pragma once
#include <SFML/Graphics.hpp>

class Time {
private:
    int timeLeft;
    sf::Font font;
    sf::Text timerText;
    sf::RectangleShape box;

public:
    Time(int startSeconds = 30);

    void update(float dt);
    void draw(sf::RenderWindow& win);
    bool isFinished() const;
};
