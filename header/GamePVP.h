#ifndef GAMEPVP_H
#define GAMEPVP_H

#include "Menu.h"
#include "NguoiQuanTro.h"
#include <array>

// Cấu trúc để lưu trữ kết quả đoán và chuỗi đoán của từng lượt
struct GuessRecord {
    std::string guess; // Chuỗi đoán (ví dụ: "1234")
    std::array<int, 8> matchStatus; // 0: Wrong, 1: Correct Position, 2: Correct Number
};

class GamePVP : public ScreenState {
private:
    std::unique_ptr<NguoiQuanTro> gameEngine; // Engine chứa key đã nhập từ NhapKeyPVP
    int maxKeyLength;
    int maxTurns = 10;
    // === TRẠNG THÁI GAME ===
    int currentTurn = 0; // Lượt đoán hiện tại
    int currentPlayer = 1; // 1: User 1 đang đoán key của User 2; 2: User 2 đang đoán key của User 1
    bool isGameOver = false;
    std::string currentInput;
    
    // Mảng lưu trữ tất cả các lượt đoán của cả hai người chơi
    std::vector<GuessRecord> user1Guesses; // Lượt đoán của U1 (đoán key của U2)
    std::vector<GuessRecord> user2Guesses; // Lượt đoán của U2 (đoán key của U1)
    
    // Mảng trạng thái màu xanh lá chuối (dùng cho các nút A B C D)
    std::array<int, 8> inputKeyStatus = {0}; // 0: Đen, 1: Xanh lá (ký tự đã dùng/hợp lệ)

    // === CÁC THÀNH PHẦN GUI DỰA TRÊN HÌNH ẢNH ===
    // Player 1 (Left) - Vị trí của người đoán
    sf::RectangleShape guessGrid1[10][8]; // Lịch sử đoán (10 lượt * 8 ký tự max)
    sf::RectangleShape resultLights1[10][2]; // Bóng đèn (xanh/đỏ) cho mỗi lượt
    sf::RectangleShape inputBoxes1[8]; // Ô nhập liệu hiện tại (HAND)
    sf::Text inputTexts1[8]; 
    
    // Player 2 (Right) - Vị trí của người đoán
    sf::RectangleShape guessGrid2[10][8]; 
    sf::RectangleShape resultLights2[10][2]; 
    sf::RectangleShape inputBoxes2[8];
    sf::Text inputTexts2[8]; 

    // Các nút ký tự A, B, C, D...
    sf::RectangleShape keyButtons1[8]; // Nút ký tự (A B C D...) cho User 1
    sf::Text keyButtonTexts1[8];
    sf::RectangleShape keyButtons2[8]; // Nút ký tự (H D R F...) cho User 2
    sf::Text keyButtonTexts2[8];

    // Trái Tim và Bóng Đèn gợi ý
    sf::CircleShape hintLights1[2]; // Bóng đèn gợi ý dưới cùng
    sf::CircleShape hintLights2[2];
    sf::RectangleShape hearts1[5];   // 5 trái tim
    sf::RectangleShape hearts2[5];

    Button guessButton; // Nút "ĐOÁN"

    // Hàm hỗ trợ
    void initializeGUI();
    void updateGUI();
    void processGuess(int playerID); // Xử lý đoán key
    void switchPlayer();
    void updateInputDisplay(int playerID);
    void drawPlayerArea(sf::RenderWindow& win, int playerID);

public:
    // Nhận Engine game đã cấu hình từ Menu
    GamePVP(sf::Font& f, float& w, float& h, float& sx, float& sy, std::unique_ptr<NguoiQuanTro> engine);
    
    GameState handleEvent(const sf::Vector2f& mousePos, sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& win) override;
};
#endif // GAMEPVP_H