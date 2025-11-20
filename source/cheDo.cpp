
/*
#include "CheDo.h"

// Constructor của CheDo: chỉ khởi tạo các nút chọn chế độ
CheDo::CheDo(sf::Font& f, float& w, float& h, float& sx, float& sy, bool& pvpStatus, int& gameLevel) : ScreenState(f, w, h, sx, sy), pvp(pvpStatus), level(gameLevel) {
    
    // === MÀN HÌNH CHỌN CHẾ ĐỘ (MODE_SELECT) ===
    modeBtns.emplace_back(L"NGƯỜI VS NGƯỜI", font, 200, 40);
    modeBtns.emplace_back(L"NGƯỜI VS MÁY",font, 300, 40);
    modeBtns.emplace_back(L"QUAY LẠI", font, 400, 38);
}

GameState CheDo::handleEvent(const sf::Vector2f& mousePos, sf::Event& e) {
    GameState nextState = MODE_SELECT;

    if (e.type == sf::Event::MouseMoved) {
        for (auto& b : modeBtns) b.hovered = b.contains(mousePos.x, mousePos.y);
    }

    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
        if (modeBtns[0].contains(mousePos.x, mousePos.y)) { 
            pvp = true; 
            nextState = GAME_PVP; // Chế độ PVP không cần chọn độ khó, chuyển thẳng vào game
        }
        else if (modeBtns[1].contains(mousePos.x, mousePos.y)) { 
            pvp = false; 
            nextState = LEVEL_SELECT; // Chế độ PVC cần chọn độ khó
        }
        else if (modeBtns[2].contains(mousePos.x, mousePos.y)) { 
            nextState = MAIN_MENU; // Quay lại Menu Chính
        }
    }

    return nextState;
}

void CheDo::update(float dt) {
    for (auto& b : modeBtns) b.update(dt);
}

void CheDo::draw(sf::RenderWindow& win) {
    drawHeader(win, L"CHỌN CHẾ ĐỘ CHƠI", 80);
    for (auto& b : modeBtns) b.draw(win, scaleX, scaleY);
}
*/
#include "CheDo.h"

// Constructor của CheDo: chỉ khởi tạo các nút chọn chế độ
CheDo::CheDo(sf::Font& f, float& w, float& h, float& sx, float& sy, bool& pvpStatus, int& gameLevel) 
    : ScreenState(f, w, h, sx, sy), pvp(pvpStatus), level(gameLevel) {
    
    // === MÀN HÌNH CHỌN CHẾ ĐỘ (MODE_SELECT) ===
    modeBtns.emplace_back(L"NGƯỜI VS NGƯỜI", font, 200, 40);
    modeBtns.emplace_back(L"NGƯỜI VS MÁY",font, 300, 40);
    modeBtns.emplace_back(L"QUAY LẠI", font, 400, 38);
}

GameState CheDo::handleEvent(const sf::Vector2f& mousePos, sf::Event& e) {
    GameState nextState = MODE_SELECT;

    if (e.type == sf::Event::MouseMoved) {
        for (auto& b : modeBtns) b.hovered = b.contains(mousePos.x, mousePos.y);
    }

    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
        if (modeBtns[0].contains(mousePos.x, mousePos.y)) { 
            // CHỌN NGƯỜI VS NGƯỜI (PvP)
            pvp = true; 
            // Luôn chuyển sang màn hình CHỌN ĐỘ KHÓ (LEVEL_SELECT)
            nextState = LEVEL_SELECT; 
        }
        else if (modeBtns[1].contains(mousePos.x, mousePos.y)) { 
            // CHỌN NGƯỜI VS MÁY (PvC)
            pvp = false; 
            // Luôn chuyển sang màn hình CHỌN ĐỘ KHÓ (LEVEL_SELECT)
            nextState = LEVEL_SELECT; 
        }
        else if (modeBtns[2].contains(mousePos.x, mousePos.y)) { 
            nextState = MAIN_MENU; 
        }
    }

    return nextState;
}

void CheDo::update(float dt) {
    for (auto& b : modeBtns) b.update(dt);
}

void CheDo::draw(sf::RenderWindow& win) {
    drawHeader(win, L"CHỌN CHẾ ĐỘ CHƠI", 80);
    for (auto& b : modeBtns) b.draw(win, scaleX, scaleY);
}