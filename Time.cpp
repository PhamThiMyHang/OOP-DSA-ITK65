#include "Time.h"
#include <iostream>

Time::Time(int startSeconds) {
    timeLeft = startSeconds;

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Không tìm thấy arial.ttf!\n";
    }

    timerText.setFont(font);
    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::Yellow);
    timerText.setStyle(sf::Text::Bold);
    timerText.setPosition(40, 30);

    box.setSize({200, 80});
    box.setFillColor(sf::Color(0, 0, 0, 150));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(3);
    box.setPosition(20, 20);
}

void Time::update(float dt) {
    static float accumulator = 0;
    accumulator += dt;

    if (accumulator >= 1.0f) {
        accumulator = 0;
        if (timeLeft > 0)
            timeLeft--;
    }

    timerText.setString("Time: " + std::to_string(timeLeft));
}

void Time::draw(sf::RenderWindow& win) {
    win.draw(box);
    win.draw(timerText);
}

bool Time::isFinished() const {
    return timeLeft <= 0;
}
