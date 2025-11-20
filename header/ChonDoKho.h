#ifndef CHONDOKHO_H
#define CHONDOKHO_H

// Cần include Menu.h để biết định nghĩa của ScreenState, Button, và GameState
#include "Menu.h"

// Lớp ChonDoKho sẽ quản lý các nút: Dễ, Trung Bình, Khó, Quay Lại
class ChonDoKho : public ScreenState {
private:
    std::vector<Button> levelBtns;
    
    // Biến để lưu trạng thái được chọn từ lớp cha (Menu)
    bool& pvp; 
    int& level;

public:
    // Thêm tham chiếu đến pvp và level để cập nhật trạng thái game
    ChonDoKho(sf::Font& f, float& w, float& h, float& sx, float& sy, bool& pvpStatus, int& gameLevel);
    
    GameState handleEvent(const sf::Vector2f& mousePos, sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& win) override;
};

#endif