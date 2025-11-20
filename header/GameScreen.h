#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Menu.h" // Cần để biết ScreenState, GameState, Button
#include "NguoiQuanTro.h" // Cần để sử dụng Game Engine

// Định nghĩa trạng thái nội bộ của GameScreen (ví dụ: đang đoán, đang xem kết quả)
enum GameSubState {
    GUESSING,
    GAME_OVER
};

class GameScreen : public ScreenState {
private:
    NguoiQuanTro gameEngine; // Đối tượng logic game
    GameSubState subState = GUESSING;

    // Các biến trạng thái game được thiết lập từ Menu
    bool isPVP;
    int selectedLevel;

    // === CÁC THÀNH PHẦN GUI TRONG GAME ===
    
    // Nút và ô nhập liệu
    sf::Text inputDisplay; // Hiển thị chuỗi đoán hiện tại
    std::vector<Button> controlBtns; // Ví dụ: Nút Đoán, Nút Gợi ý, Nút Lịch sử

    // Cấu hình dựa trên NguoiQuanTro
    int maxKeyLength;
    int maxGuesses;
    
    // === LƯỚI Ô VUÔNG (Key/Đoán) ===
    sf::RectangleShape guessGrid[10][8]; // Vd: 10 lần đoán, 8 ký tự max
    std::vector<sf::Text> guessText[10]; // Lưu các ký tự đã đoán

    // === TRÁI TIM (Lượt chơi/Mạng) ===
    sf::RectangleShape hearts[3]; // Vd: 3 mạng (hoặc 3 lượt sai)
    
    // === BÓNG ĐÈN (Gợi ý/Kết quả) ===
    sf::CircleShape hintLights[2]; // Vd: Bóng đèn 1: Đúng vị trí, Bóng đèn 2: Đúng số
    sf::Color lightOn = sf::Color(255, 255, 0); // Vàng sáng
    sf::Color lightOff = sf::Color(50, 50, 50); // Xám tối


    // Các hàm hỗ trợ
    void setupGameEngine();
    void drawHearts(sf::RenderWindow& win);
    void drawGuessGrid(sf::RenderWindow& win);
    void drawHintLights(sf::RenderWindow& win);
    // ...

public:
    GameScreen(sf::Font& f, float& w, float& h, float& sx, float& sy, bool pvpMode, int levelIndex);
    
    GameState handleEvent(const sf::Vector2f& mousePos, sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& win) override;

    // Thêm hàm xử lý đoán
    void processGuess(const std::string& guess); 
};

#endif