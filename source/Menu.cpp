
#include "Menu.h"
#include "CheDo.h" 
#include "ChonDoKho.h"
#include "../header/GameScreen.h" // Nên đổi thành GamePVP.h và GamePVC.h
#include "../header/NhapKeyPVP.h"  // <--- THÊM INCLUDE NÀY
#include "../header/NhapKeyPVC.h"  // <--- THÊM INCLUDE NÀY
#include "../header/GamePVP.h"     // <--- THÊM INCLUDE NÀY
//#include "../header/GamePVC.h"     // <--- THÊM INCLUDE NÀY

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

// ==================== HÀM HỖ TRỢ ====================
// Hàm cực kỳ quan trọng: căn giữa chính xác một sf::Text
void centerText(sf::Text& txt) {
    // getLocalBounds() trả về hình chữ nhật bao quanh chữ
    // .top thường là số âm → phải cộng lại để origin rơi đúng giữa chữ
    txt.setOrigin(txt.getLocalBounds().width / 2.f, 
                  txt.getLocalBounds().height / 2.f + txt.getLocalBounds().top);
}
std::unique_ptr<NguoiQuanTro> heldGameEngine = nullptr; 
// ==================== BUTTON ====================
// Constructor của nút bấm
Button::Button(const std::wstring& s, sf::Font& f, float y, unsigned sz) : baseY(y), baseSize(sz) {
    text.setFont(f);
    // Dùng wstring để hỗ trợ tốt nhất các ký tự Unicode tiếng Việt
    text.setString(s); 
    text.setCharacterSize(sz);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    centerText(text);

    box.setSize({720, 100});
    box.setOrigin(360, 50); // Đặt origin vào giữa hình chữ nhật
    box.setFillColor(sf::Color(20, 20, 90)); // Màu nền: xanh tím đậm
    box.setOutlineThickness(6);
    box.setOutlineColor(sf::Color(0, 200, 255)); // Màu viền: cyan sáng
}

// Kiểm tra chuột có đang nằm trong nút không
bool Button::contains(float x, float y) const {
    return box.getGlobalBounds().contains(x, y);
}

// Hiệu ứng hover: phóng to khi chuột di vào, thu nhỏ khi ra
void Button::update(float dt) {
    float target = hovered ? 1.18f : 1.0f;
    float current = box.getScale().x;
    // Nội suy mượt (lerp) theo thời gian
    current += (target - current) * dt * 12.0f; 
    box.setScale(current, current);
}

// Vẽ nút lên màn hình
void Button::draw(sf::RenderWindow& win, float sx, float sy) {
    float centerX = win.getSize().x / 2.0f;
    float posY = baseY * sy; // Tính vị trí Y thực tế theo tỉ lệ responsive

    box.setPosition(centerX, posY);
    text.setPosition(centerX, posY);

    // QUAN TRỌNG: Resize chữ theo cửa sổ
    unsigned newSize = static_cast<unsigned>(baseSize * ((sx + sy) / 2));
    text.setCharacterSize(newSize);
    centerText(text); // Cập nhật lại origin

    win.draw(box);
    win.draw(text);
}

// ==================== LỚP MÀN HÌNH CƠ SỞ (ScreenState) ====================
// Constructor
ScreenState::ScreenState(sf::Font& f, float& w, float& h, float& sx, float& sy)
    : font(f), winW(w), winH(h), scaleX(sx), scaleY(sy) {}

// Hàm vẽ tiêu đề phụ chung
void ScreenState::drawHeader(sf::RenderWindow& win, const std::wstring& s, float yOffset) {
    sf::Text header;
    header.setFont(font);
    header.setFillColor(sf::Color(100, 230, 255));
    header.setOutlineColor(sf::Color::Cyan);
    header.setOutlineThickness(5);
    
    header.setString(s);
    header.setCharacterSize(static_cast<unsigned>(72 * scaleY));
    centerText(header);
    header.setPosition(winW / 2.0f, yOffset * scaleY);
    win.draw(header);
}

// ==================== MENU CHÍNH (Quản lý trạng thái) ====================
// Tạo nền vũ trụ với các ngôi sao ngẫu nhiên
void Menu::createBackground() {
    sf::Image img;
    img.create(900, 600, sf::Color(12, 12, 40));
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < 220; ++i) {
        int x = rand() % 900, y = rand() % 600;
        img.setPixel(x, y, sf::Color(80, 180, 255, 65));
    }
    bgTex.loadFromImage(img);
    bg.setTexture(bgTex);
}

// Tính lại tỉ lệ khi cửa sổ thay đổi kích thước
void Menu::recalcScale() {
    scaleX = winW / 900.0f;
    scaleY = winH / 600.0f;
    bg.setScale(scaleX, scaleY);
}

// Chuyển đổi giữa các trạng thái màn hình con
void Menu::switchState(GameState newState) {
    currentState = newState;
    currentScreen = nullptr; // Xóa màn hình cũ (giải phóng bộ nhớ)

    // Khởi tạo màn hình mới dựa trên trạng thái
    if (currentState == MODE_SELECT) {
        // ... (Khởi tạo CheDo) ...
        currentScreen = std::make_unique<CheDo>(font, winW, winH, scaleX, scaleY, pvpStatus, gameLevel);
    } else if (currentState == LEVEL_SELECT) {
        // ... (Khởi tạo ChonDoKho) ...
        currentScreen = std::make_unique<ChonDoKho>(font, winW, winH, scaleX, scaleY, pvpStatus, gameLevel);
    }
    // ============== NHẬP KEY MỚI ==================
    else if (currentState == NHAP_KEY_PVP) {
        // Khởi tạo NhapKeyPVP, truyền level đã chọn
        currentScreen = std::make_unique<NhapKeyPVP>(font, winW, winH, scaleX, scaleY, gameLevel);
    }
    else if (currentState == NHAP_KEY_PVC) {
        // Khởi tạo NhapKeyPVC, truyền level đã chọn
        currentScreen = std::make_unique<NhapKeyPVC>(font, winW, winH, scaleX, scaleY, gameLevel);
    }
    // ============== BẮT ĐẦU CHƠI (CHUYỂN GIAO ENGINE) ==================
    else if (currentState == GAME_PVP) {
        // 1. Lấy Engine đã cấu hình (chứa Keys) từ màn hình NhapKeyPVP vừa thoát
        NhapKeyPVP* prevScreen = dynamic_cast<NhapKeyPVP*>(currentScreen.get());
        if (prevScreen) {
            heldGameEngine = prevScreen->releaseGameEngine(); // Lấy Engine
        }
        
        // 2. Khởi tạo GamePVP, chuyển giao quyền sở hữu Engine
        currentScreen = std::make_unique<GamePVP>(font, winW, winH, scaleX, scaleY, std::move(heldGameEngine));
        heldGameEngine = nullptr; // Đã chuyển giao
    }
  /*  else if (currentState == GAME_PVC) {
        // 1. Lấy Engine đã cấu hình (chứa Key) từ màn hình NhapKeyPVC vừa thoát
        NhapKeyPVC* prevScreen = dynamic_cast<NhapKeyPVC*>(currentScreen.get());
        if (prevScreen) {
            heldGameEngine = prevScreen->releaseGameEngine(); // Lấy Engine
        }

        // 2. Khởi tạo GamePVC, chuyển giao quyền sở hữu Engine
        currentScreen = std::make_unique<GamePVC>(font, winW, winH, scaleX, scaleY, std::move(heldGameEngine));
        heldGameEngine = nullptr;
    }*/
    // ... (Thêm các trạng thái khác: MAIN_MENU, HOW_TO_PLAY, SETTINGS) ...
}

// Constructor chính của Menu
Menu::Menu(float w, float h) : winW(w), winH(h) {
    // Tải font (nên dùng đường dẫn tương đối hoặc đảm bảo có font)
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "KHÔNG TÌM THẤY FONT ARIAL.TTF!\n";
    }

    createBackground(); // Tạo nền sao
    recalcScale();      // Tính tỉ lệ ban đầu

    // Thiết lập tiêu đề chính "GUESS ARENA"
    title.setFont(font);
    title.setString(L"GUESS ARENA");
    title.setCharacterSize(96);
    title.setFillColor(sf::Color(100, 230, 255));
    title.setOutlineColor(sf::Color::Cyan);
    title.setOutlineThickness(4);
    title.setStyle(sf::Text::Bold);
    centerText(title);

    // === TẠO CÁC NÚT TRONG MAIN MENU ===
    mainBtns.emplace_back(L"BẮT ĐẦU",font, 220);
    mainBtns.emplace_back(L"HƯỚNG DẪN", font, 320);
    mainBtns.emplace_back(L"CÀI ĐẶT",font, 420);
    mainBtns.emplace_back(L"THOÁT", font, 520);
    
    // Khởi tạo trạng thái ban đầu là MAIN_MENU
    switchState(MAIN_MENU); 
}

// Khi cửa sổ bị resize (kéo to/thu nhỏ)
void Menu::resize(float w, float h) {
    winW = w;
    winH = h;
    recalcScale();
}

// Xử lý tất cả sự kiện: chuột di chuyển, click, cuộn chuột...
void Menu::handleEvent(sf::RenderWindow& win, sf::Event& e) {
    sf::Vector2f m = win.mapPixelToCoords(sf::Mouse::getPosition(win)); // Tọa độ chuột chính xác
    GameState nextState = currentState;

    if (currentState == MAIN_MENU) {
        // Xử lý hover và click cho Menu Chính
        if (e.type == sf::Event::MouseMoved) {
            for (auto& b : mainBtns) b.hovered = b.contains(m.x, m.y);
        }
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (mainBtns[0].contains(m.x, m.y)) nextState = MODE_SELECT;
            else if (mainBtns[1].contains(m.x, m.y)) nextState = HOW_TO_PLAY;
            else if (mainBtns[2].contains(m.x, m.y)) nextState = SETTINGS;
            else if (mainBtns[3].contains(m.x, m.y)) nextState = CONFIRM_EXIT;
        }
    } else if (currentScreen) {
        // Chuyển việc xử lý sự kiện cho màn hình con hiện tại
        nextState = currentScreen->handleEvent(m, e);
    }
    
    // Nếu trạng thái thay đổi, thực hiện chuyển đổi
    if (nextState != currentState) {
        if (nextState == CONFIRM_EXIT) win.close(); // Xử lý thoát nhanh (có thể thay bằng logic ConfirmExit phức tạp hơn)
        else switchState(nextState);
    }
}

// Cập nhật animation mỗi frame
void Menu::update() {
    animTime += 1.0f / 60.0f; // Tăng thời gian animation (giả sử 60 FPS)

    if (currentState == MAIN_MENU) {
        for (auto& b : mainBtns) b.update(1.0f / 60.0f);
    } else if (currentScreen) {
        // Cập nhật màn hình con hiện tại
        currentScreen->update(1.0f / 60.0f);
    }
}

// Vẽ toàn bộ menu lên màn hình
void Menu::draw(sf::RenderWindow& win) {
    win.draw(bg); // Vẽ nền vũ trụ

    float centerX = win.getSize().x / 2.0f;
    
    if (currentState == MAIN_MENU) {
        // Vẽ logo chính với hiệu ứng "thở"
        title.setCharacterSize(static_cast<unsigned>(96 * scaleY));
        centerText(title);
        title.setPosition(centerX, 90 * scaleY);
        title.setOutlineThickness(4 + 0.8f * sin(animTime * 2)); // Viền nhấp nháy
        win.draw(title);

        // Vẽ các nút Menu Chính
        for (auto& b : mainBtns) b.draw(win, scaleX, scaleY);
    } else if (currentScreen) {
        // Vẽ màn hình con hiện tại (CheDo, CachChoi, CaiDat,...)
        currentScreen->draw(win);
    }
}





// ... (Phần Menu::Menu, Menu::resize, Menu::handleEvent, Menu::update, Menu::draw giữ nguyên)