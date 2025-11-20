#ifndef NHAPKEYPVC_H
#define NHAPKEYPVC_H

#include "Menu.h"
#include "NguoiQuanTro.h"

// Trạng thái nội bộ của màn hình nhập key PvC
enum PVCScreenState {
    USER_INPUT,    // Chờ User 1 nhập key
    COMPUTER_SETUP // Computer tạo key và sẵn sàng chuyển sang game
};

class NhapKeyPVC : public ScreenState {
private:
    std::unique_ptr<NguoiQuanTro> gameEngine = nullptr;
    PVCScreenState subState = USER_INPUT; // Bắt đầu bằng việc chờ User nhập key
    
    int maxKeyLength;
    std::string currentKeyInput;

    // === CÁC THÀNH PHẦN GUI DỰA TRÊN HÌNH ẢNH ===
    // Khu vực User 1 (Bên trái)
    sf::RectangleShape playerBox1;
    sf::Text playerText1;
    sf::Sprite playerIcon1;
    sf::RectangleShape keyInputFrame1;
    sf::RectangleShape keyBoxes1[8];
    sf::Text keyCharTexts1[8];
    
    // Khu vực Computer (Bên phải)
    sf::RectangleShape playerBox2; // Ô chứa COMPUTER
    sf::Text playerText2;         // Chữ COMPUTER
    sf::Sprite playerIcon2;       // Icon Computer
    sf::RectangleShape keyInputFrame2;
    sf::RectangleShape keyBoxes2[8];
    sf::Text keyCharTexts2[8];    // Hiển thị key đã tạo (hoặc placeholder)

    sf::Text promptText;
    Button confirmButton;
    Button startButton;           // Nút "BẮT ĐẦU CHƠI" (xuất hiện sau khi computer setup xong)

    int selectedLevel;

    // Hàm hỗ trợ
    void setupGameEngine();
    void resetInputDisplay();
    void updateKeyCharDisplays();
    void drawKeyInputArea(sf::RenderWindow& win, int user);

public:
    NhapKeyPVC(sf::Font& f, float& w, float& h, float& sx, float& sy, int levelIndex);
    
    GameState handleEvent(const sf::Vector2f& mousePos, sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& win) override;

    std::unique_ptr<NguoiQuanTro> releaseGameEngine() {
        return std::move(gameEngine);
    }
};

#endif // NHAPKEYPVC_H