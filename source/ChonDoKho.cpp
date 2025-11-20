#include "ChonDoKho.h"

// Enum cho trạng thái nội bộ của ChonDoKho
enum LevelState {
    LEVEL_SELECT_SCREEN
};

// Constructor (khởi tạo các nút độ khó và tham chiếu biến trạng thái)
ChonDoKho::ChonDoKho(sf::Font& f, float& w, float& h, float& sx, float& sy, bool& pvpStatus, int& gameLevel)
    : ScreenState(f, w, h, sx, sy), pvp(pvpStatus), level(gameLevel) {
    
    // === KHỞI TẠO CÁC NÚT ĐỘ KHÓ (LEVEL_SELECT) ===
    levelBtns.emplace_back(L"DỄ",font, 170, 58);
    levelBtns.emplace_back(L"TRUNG BÌNH", font, 270, 58);
    levelBtns.emplace_back(L"KHÓ",font, 370, 58);
    levelBtns.emplace_back(L"QUAY LẠI",font, 470, 48);
}

GameState ChonDoKho::handleEvent(const sf::Vector2f& mousePos, sf::Event& e) {
    GameState nextState = LEVEL_SELECT; 

    if (e.type == sf::Event::MouseMoved) {
        for (auto& b : levelBtns) b.hovered = b.contains(mousePos.x, mousePos.y);
    }

    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
        
        // --- LOGIC PHÂN LUỒNG QUAN TRỌNG NHẤT ---
        // Sau khi chọn độ khó, bước tiếp theo là Nhập Key tương ứng.
        GameState nextInputStep = pvp ? NHAP_KEY_PVP : NHAP_KEY_PVC;
        // ----------------------------------------

        if (levelBtns[0].contains(mousePos.x, mousePos.y)) { 
            level = 0; // DỄ
            nextState = nextInputStep; 
        } 
        else if (levelBtns[1].contains(mousePos.x, mousePos.y)) { 
            level = 1; // TRUNG BÌNH
            nextState = nextInputStep;
        } 
        else if (levelBtns[2].contains(mousePos.x, mousePos.y)) { 
            level = 2; // KHÓ
            nextState = nextInputStep; 
        } 
        else if (levelBtns[3].contains(mousePos.x, mousePos.y)) { 
            nextState = MODE_SELECT; // Quay lại màn hình chọn Chế độ
        }
    }

    return nextState;
}
void ChonDoKho::update(float dt) {
    for (auto& b : levelBtns) b.update(dt);
}

void ChonDoKho::draw(sf::RenderWindow& win) {
    drawHeader(win, L"CHỌN ĐỘ KHÓ", 80);
    for (auto& b : levelBtns) b.draw(win, scaleX, scaleY);
}