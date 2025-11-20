#ifndef CHONDOKHO_H
#define CHEDO_H
#include "Menu.h"

// Lớp CheDo sẽ quản lý các nút: Người vs Người, Người vs Máy, Quay Lại
class CheDo : public ScreenState {
private:
    std::vector<Button> modeBtns;
    std::vector<Button> levelBtns;
public:
    CheDo(sf::Font& f, float& w, float& h, float& sx, float& sy, bool& pvpStatus, int& gameLevel);
    
    // Trả về trạng thái tiếp theo sau khi click
    GameState handleEvent(const sf::Vector2f& mousePos, sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& win) override;

    // Các biến cần thiết cho logic game
    bool pvp = true; 
    int level = 0;
};
#endif