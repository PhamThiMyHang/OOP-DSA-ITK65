#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

enum GameState { MAIN_MENU, MODE_SELECT, LEVEL_SELECT, HOW_TO_PLAY, SETTINGS, CONFIRM_EXIT, GAME_PVP, GAME_PVC };

class Menu {
private:
    sf::Font font;
    sf::Texture bgTex; sf::Sprite bg;
    GameState state = MAIN_MENU;
    float animTime = 0.0f;
    float scrollOffset = 0.0f;

    float winW = 900, winH = 600;
    float scaleX = 1.0f, scaleY = 1.0f;

    struct Button {
        sf::Text text;
        sf::RectangleShape box;
        bool hovered = false;
        float baseY = 0;
        unsigned baseSize = 42;
        Button(const std::wstring& s, sf::Font& f, float y, unsigned sz = 42);
        bool contains(float x, float y) const;
        void update(float dt);
        void draw(sf::RenderWindow& win, float sx, float sy);
    };

    sf::Text title;
    std::vector<Button> mainBtns, modeBtns, levelBtns, backBtn, confirmBtns;

    void createBackground();
    void recalcScale();

public:
    Menu(float w = 900, float h = 600);
    void resize(float w, float h);
    void handleEvent(sf::RenderWindow& win, sf::Event& e);
    void update();
    void draw(sf::RenderWindow& win);

    GameState getState() const { return state; }
    void reset() { state = MAIN_MENU; scrollOffset = 0; }

    int level = 0;
    bool pvp = false;
};

#endif