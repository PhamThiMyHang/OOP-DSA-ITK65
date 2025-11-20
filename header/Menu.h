#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory> // Dùng cho std::unique_ptr

// ==================== KHAI BÁO SỚM ====================
class CheDo; // Khai báo sớm để tránh định nghĩa lại lớp (Redefinition error)
class ChonDoKho;
class NhapKeyPVP;
class NhapKeyPVC; // Lớp mới
class GamePVP;    // Lớp mới
class GamePVC;    // Lớp mới
// Định nghĩa các trạng thái (để lớp Menu quản lý chuyển đổi)

enum GameState {
    MAIN_MENU,
    MODE_SELECT,
    LEVEL_SELECT,
    NHAP_KEY_PVP,  // PvP: Nhập Key (User 1, User 2)
    NHAP_KEY_PVC,  // PvC: Nhập Key (User 1)
    HOW_TO_PLAY,
    SETTINGS,
    CONFIRM_EXIT,
    GAME_PVP,
    GAME_PVC
};

// ==================== HÀM HỖ TRỢ ====================
void centerText(sf::Text& txt);

// ==================== LỚP NÚT (Button) ====================
class Button {
private:
    float baseY;
    unsigned baseSize;
public:
    sf::RectangleShape box;
    sf::Text text;
    bool hovered = false;
    
    Button(const std::wstring& s, sf::Font& f, float y, unsigned sz = 50);

    // Kích thước/vị trí X, Y (tính theo tỉ lệ chuẩn 900x600)
    bool contains(float x, float y) const;
    
    // Cập nhật hiệu ứng hover
    void update(float dt); 
    
    // Vẽ nút (sx, sy là tỉ lệ phóng to/thu nhỏ)
    void draw(sf::RenderWindow& win, float sx, float sy);
};

// ==================== LỚP MÀN HÌNH CƠ SỞ (ScreenState) ====================
// Lớp trừu tượng cho mọi màn hình con (main, chế độ, cài đặt, ...)
class ScreenState {
protected:
    sf::Font& font;
    float& winW;
    float& winH;
    float& scaleX;
    float& scaleY;
    std::vector<Button> buttons;
    
    // Tiêu đề cho các màn hình phụ
    void drawHeader(sf::RenderWindow& win, const std::wstring& s, float yOffset);
public:
    ScreenState(sf::Font& f, float& w, float& h, float& sx, float& sy);
    virtual ~ScreenState() = default;

    // Trả về trạng thái tiếp theo sau khi click
    virtual GameState handleEvent(const sf::Vector2f& mousePos, sf::Event& e) = 0; 
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& win) = 0;
};


// (***ĐÃ XÓA*** Định nghĩa lớp CheDo đầy đủ ở đây để tránh lỗi Redefinition)


// ==================== LỚP MENU CHÍNH (Quản lý trạng thái) ====================
class Menu {
private:
    sf::Font font;
    sf::Texture bgTex;
    sf::Sprite bg;
    sf::Text title;

    float winW, winH;
    float scaleX, scaleY;
    float animTime = 0.0f;

    // === BIẾN TRẠNG THÁI GAME ===
    bool pvpStatus = true; // Lưu chế độ chơi: true = PvP, false = PvC
    int gameLevel = 0;     // Lưu độ khó (0: Dễ, 1: TB, 2: Khó)
    // ===========================
    
    GameState currentState = MAIN_MENU;

    // Trạng thái hiện tại được quản lý bởi con trỏ thông minh
    std::unique_ptr<ScreenState> currentScreen = nullptr;
    
    // Các màn hình cố định
    std::vector<Button> mainBtns; // Vẫn giữ các nút menu chính ở đây
    
    // Hàm khởi tạo và chuyển trạng thái
    void createBackground();
    void recalcScale();
    void switchState(GameState newState);

public:
    Menu(float w, float h);
    void resize(float w, float h);
    void handleEvent(sf::RenderWindow& win, sf::Event& e);
    void update();
    void draw(sf::RenderWindow& win);
    
    GameState getState() const { return currentState; }
    // Có thể thêm hàm lấy trạng thái game sau khi chọn
};
#endif