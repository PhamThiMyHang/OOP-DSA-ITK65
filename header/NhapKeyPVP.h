#ifndef NHAPKEYPVP_H
#define NHAPKEYPVP_H

#include "Menu.h"          // Kế thừa ScreenState
#include "NguoiQuanTro.h"  // Sử dụng game logic

class NhapKeyPVP : public ScreenState {
private:
    std::unique_ptr<NguoiQuanTro> gameEngine = nullptr; // Engine game được khởi tạo tại đây
    
    int currentInputUser = 1; // 1: User 1 nhập; 2: User 2 nhập
    int maxKeyLength;         // Số ký tự key (từ NguoiQuanTro)
    std::string currentKeyInput;
    std::string keyUser1_set; // Lưu key tạm thời của User 1
    std::string keyUser2_set; // Lưu key tạm thời của User 2

    // === CÁC THÀNH PHẦN GUI DỰA TRÊN HÌNH ẢNH ===
    sf::RectangleShape playerBox1; // Ô chứa PLAYER 1
    sf::RectangleShape playerBox2; // Ô chứa PLAYER 2
    sf::Text playerText1;         // Chữ PLAYER 1
    sf::Text playerText2;         // Chữ PLAYER 2
    sf::Sprite playerIcon1;       // Icon người chơi 1
    sf::Sprite playerIcon2;       // Icon người chơi 2
    sf::Texture playerIconTex;    // Texture cho icon người chơi

    // Khung chứa các ô nhập key (HAND trên hình)
    sf::RectangleShape keyInputFrame1; 
    sf::RectangleShape keyInputFrame2;

    // Các ô vuông cho từng ký tự của Key (HAND)
    sf::RectangleShape keyBoxes1[8]; // Giả sử max 8 ký tự
    sf::RectangleShape keyBoxes2[8];
    sf::Text keyCharTexts1[8];      // Text cho từng ký tự
    sf::Text keyCharTexts2[8];

    sf::Text promptText;            // Nhắc nhở: "PLAYER 1: Enter your key"
    Button confirmButton;           // Nút "XÁC NHẬN"

    // Các biến trạng thái từ Menu
    int selectedLevel; // Cần để cấu hình NguoiQuanTro

    // Hàm hỗ trợ
    void setupGameEngine();           // Khởi tạo NguoiQuanTro và lấy maxKeyLength
    void resetInputDisplay(int user); // Reset các ô nhập và chuỗi input
    void updateKeyCharDisplays();     // Cập nhật các ký tự trong ô vuông
    void drawKeyInputArea(sf::RenderWindow& win, int user); // Vẽ khu vực nhập key cho người chơi

public:
    NhapKeyPVP(sf::Font& f, float& w, float& h, float& sx, float& sy, int levelIndex);
    
    GameState handleEvent(const sf::Vector2f& mousePos, sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& win) override;

    // Hàm để Menu lấy engine đã cấu hình
    std::unique_ptr<NguoiQuanTro> releaseGameEngine() {
        return std::move(gameEngine);
    }
};

#endif // NHAPKEYPVP_H