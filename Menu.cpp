
#include "Menu.h"                  // File header chứa khai báo lớp Menu và Button
#include <iostream>                // Dùng để in lỗi ra console (std::cerr)
#include <cmath>                   // Dùng hàm sin() để tạo hiệu ứng nhấp nháy, "thở"
#include <cstdlib>                 // Dùng srand(), rand() để tạo số ngẫu nhiên cho ngôi sao nền
#include <ctime>                   // Dùng time() để gieo mầm (seed) cho rand()

// ==================== HÀM HỖ TRỢ ====================
// Hàm cực kỳ quan trọng: căn giữa chính xác một sf::Text
// Phải gọi lại mỗi khi thay đổi nội dung (setString) hoặc kích thước chữ (setCharacterSize)
void centerText(sf::Text& txt) {
    // getLocalBounds() trả về hình chữ nhật bao quanh chữ
    // .top thường là số âm → phải cộng lại để origin rơi đúng giữa chữ
    txt.setOrigin(txt.getLocalBounds().width / 2.f, 
                  txt.getLocalBounds().height / 2.f + txt.getLocalBounds().top);
}

// ==================== BUTTON ====================
// Constructor của nút bấm
Menu::Button::Button(const std::wstring& s, sf::Font& f, float y, unsigned sz)
    : baseY(y), baseSize(sz) {                    // Gán vị trí Y cơ sở và kích thước chữ cơ sở
    text.setFont(f);                              // Gán font cho chữ trên nút
    text.setString(s);                            // Nội dung chữ (ví dụ: L"BẮT ĐẦU")
    text.setCharacterSize(sz);                    // Kích thước chữ ban đầu
    text.setFillColor(sf::Color::White);          // Màu chữ: trắng
    text.setStyle(sf::Text::Bold);                // Chữ in đậm
    centerText(text);                             // Căn giữa chữ ngay từ đầu

    box.setSize({720, 100});                      // Kích thước nền nút: rộng 720, cao 100 (to, dễ bấm)
    box.setOrigin(360, 50);                       // Đặt origin vào giữa hình chữ nhật
    box.setFillColor(sf::Color(20, 20, 90));      // Màu nền: xanh tím đậm
    box.setOutlineThickness(6);                   // Độ dày viền
    box.setOutlineColor(sf::Color(0, 200, 255));  // Màu viền: cyan sáng
}

// Kiểm tra chuột có đang nằm trong nút không
bool Menu::Button::contains(float x, float y) const {
    return box.getGlobalBounds().contains(x, y);  // getGlobalBounds() trả về vùng thực tế trên màn hình
}

// Hiệu ứng hover: phóng to khi chuột di vào, thu nhỏ khi ra
void Menu::Button::update(float dt) {
    float target = hovered ? 1.18f : 1.0f;        // Nếu đang hover → phóng to 1.18x, không thì 1x
    float current = box.getScale().x;             // Lấy tỉ lệ hiện tại
    current += (target - current) * dt * 12.0f;   // Nội suy mượt (lerp) theo thời gian
    box.setScale(current, current);               // Áp dụng tỉ lệ mới cho cả X và Y
}

// Vẽ nút lên màn hình – được gọi mỗi frame
void Menu::Button::draw(sf::RenderWindow& win, float sx, float sy) {
    float centerX = win.getSize().x / 2.0f;       // Tâm ngang của cửa sổ
    float posY = baseY * sy;                      // Tính vị trí Y thực tế theo tỉ lệ responsive

    box.setPosition(centerX, posY);               // Đặt vị trí nền nút
    text.setPosition(centerX, posY);              // Đặt vị trí chữ

    // QUAN TRỌNG: Khi resize cửa sổ → chữ phải thay đổi kích thước theo
    unsigned newSize = static_cast<unsigned>(baseSize * ((sx + sy) / 2));
    text.setCharacterSize(newSize);               // Cập nhật kích thước chữ
    centerText(text);                             // Cập nhật lại origin (vì kích thước thay đổi → bounds thay đổi)

    win.draw(box);                                // Vẽ nền trước
    win.draw(text);                               // Vẽ chữ sau (nằm trên nền)
}

// ==================== MENU ====================
// Tạo nền vũ trụ với các ngôi sao ngẫu nhiên
void Menu::createBackground() {
    sf::Image img;
    img.create(900, 600, sf::Color(12, 12, 40));  // Tạo ảnh 900x600 màu xanh đen vũ trụ
    srand(time(nullptr));                         // Gieo mầm ngẫu nhiên bằng thời gian hiện tại
    for (int i = 0; i < 220; ++i) {                // Vẽ 220 ngôi sao nhỏ
        int x = rand() % 900, y = rand() % 600;   // Tọa độ ngẫu nhiên
        img.setPixel(x, y, sf::Color(80, 180, 255, 65)); // Màu xanh sáng, trong suốt nhẹ
    }
    bgTex.loadFromImage(img);                     // Chuyển ảnh thành texture
    bg.setTexture(bgTex);                         // Gán texture cho sprite nền
}

// Tính lại tỉ lệ khi cửa sổ thay đổi kích thước
void Menu::recalcScale() {
    scaleX = winW / 900.0f;                       // Tỉ lệ theo chiều ngang
    scaleY = winH / 600.0f;                       // Tỉ lệ theo chiều dọc
    bg.setScale(scaleX, scaleY);                  // Phóng to/thu nhỏ nền cho vừa cửa sổ
}

// Constructor chính của Menu
Menu::Menu(float w, float h) : winW(w), winH(h) { // Nhận kích thước cửa sổ ban đầu
    // Tải font Arial từ Windows (đảm bảo font này có trên mọi máy Windows)
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "KHÔNG TÌM THẤY FONT ARIAL.TTF!\n"; // Báo lỗi nếu không tìm thấy
    }

    createBackground();                           // Tạo nền sao
    recalcScale();                                // Tính tỉ lệ ban đầu

    // Thiết lập tiêu đề chính "GUESS ARENA"
    title.setFont(font);
    title.setString(L"GUESS ARENA");
    title.setCharacterSize(96);
    title.setFillColor(sf::Color(100, 230, 255));
    title.setOutlineColor(sf::Color::Cyan);
    title.setOutlineThickness(4);
    title.setStyle(sf::Text::Bold);
    centerText(title);                            // Căn giữa tiêu đề

    // === TẠO CÁC NÚT TRONG MENU CHÍNH ===
    mainBtns.emplace_back(L"BẮT ĐẦU",    font, 220);    // Nút 1: Y = 220
    mainBtns.emplace_back(L"HƯỚNG DẪN", font, 320);
    mainBtns.emplace_back(L"CÀI ĐẶT",    font, 420);
    mainBtns.emplace_back(L"THOÁT",       font, 520);

    // === MÀN HÌNH CHỌN CHẾ ĐỘ ===
    modeBtns.emplace_back(L"NGƯỜI VS NGƯỜI", font, 200, 40);
    modeBtns.emplace_back(L"NGƯỜI VS MÁY",    font, 300, 40);
    modeBtns.emplace_back(L"QUAY LẠI",       font, 400, 38);

    // === MÀN HÌNH CHỌN ĐỘ KHÓ ===
    levelBtns.emplace_back(L"DỄ",         font, 170, 58);
    levelBtns.emplace_back(L"TRUNG BÌNH", font, 270, 58);
    levelBtns.emplace_back(L"KHÓ",         font, 370, 58);
    levelBtns.emplace_back(L"QUAY LẠI",    font, 470, 48);

    // Nút chung cho các màn hình phụ
    backBtn.emplace_back(L"QUAY LẠI MENU", font, 520, 42);

    // Xác nhận thoát game
    confirmBtns.emplace_back(L"CÓ, THOÁT",     font, 320, 48);
    confirmBtns.emplace_back(L"KHÔNG, Ở LẠI", font, 430, 48);
}

// Khi cửa sổ bị resize (kéo to/thu nhỏ)
void Menu::resize(float w, float h) {
    winW = w;
    winH = h;
    recalcScale();                                // Cập nhật lại tỉ lệ và nền
}

// Xử lý tất cả sự kiện: chuột di chuyển, click, cuộn chuột...
void Menu::handleEvent(sf::RenderWindow& win, sf::Event& e) {
    sf::Vector2f m = win.mapPixelToCoords(sf::Mouse::getPosition(win)); // Tọa độ chuột chính xác

    // Xử lý hover (chuột di chuyển)
    if (e.type == sf::Event::MouseMoved) {
        auto check = [&](auto& v) { for (auto& b : v) b.hovered = b.contains(m.x, m.y); };
        if (state == MAIN_MENU)      check(mainBtns);
        else if (state == MODE_SELECT) check(modeBtns);
        else if (state == LEVEL_SELECT) check(levelBtns);
        else if (state == CONFIRM_EXIT) check(confirmBtns);
        else                            check(backBtn); // HOW_TO_PLAY, SETTINGS
    }

    // Xử lý click chuột trái
    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
        if (state == MAIN_MENU) {
            if (mainBtns[0].contains(m.x, m.y)) state = MODE_SELECT;
            if (mainBtns[1].contains(m.x, m.y)) state = HOW_TO_PLAY;
            if (mainBtns[2].contains(m.x, m.y)) state = SETTINGS;
            if (mainBtns[3].contains(m.x, m.y)) state = CONFIRM_EXIT;
        }
        else if (state == MODE_SELECT) {
            if (modeBtns[0].contains(m.x, m.y)) { pvp = true;  state = LEVEL_SELECT; }
            if (modeBtns[1].contains(m.x, m.y)) { pvp = false; state = LEVEL_SELECT; }
            if (modeBtns[2].contains(m.x, m.y)) state = MAIN_MENU;
        }
        else if (state == LEVEL_SELECT) {
            if (levelBtns[0].contains(m.x, m.y)) { level = 0; state = pvp ? GAME_PVP : GAME_PVC; }
            if (levelBtns[1].contains(m.x, m.y)) { level = 1; state = pvp ? GAME_PVP : GAME_PVC; }
            if (levelBtns[2].contains(m.x, m.y)) { level = 2; state = pvp ? GAME_PVP : GAME_PVC; }
            if (levelBtns[3].contains(m.x, m.y)) state = MODE_SELECT;
        }
        else if (state == SETTINGS || state == HOW_TO_PLAY) {
            if (backBtn[0].contains(m.x, m.y)) state = MAIN_MENU;
        }
        else if (state == CONFIRM_EXIT) {
            if (confirmBtns[0].contains(m.x, m.y)) win.close();      // Thoát game
            if (confirmBtns[1].contains(m.x, m.y)) state = MAIN_MENU; // Hủy thoát
        }
    }

    // Cuộn chuột trong màn hình hướng dẫn
    if (state == HOW_TO_PLAY && e.type == sf::Event::MouseWheelScrolled)
        scrollOffset += e.mouseWheelScroll.delta * 70; // Cuộn nội dung lên/xuống
}

// Cập nhật animation mỗi frame
void Menu::update() {
    animTime += 1.0f / 60.0f;                     // Tăng thời gian animation (giả sử 60 FPS)
    for (auto& b : mainBtns)   b.update(1.0f / 60.0f);
    for (auto& b : modeBtns)   b.update(1.0f / 60.0f);
    for (auto& b : levelBtns)  b.update(1.0f / 60.0f);
    for (auto& b : backBtn)    b.update(1.0f / 60.0f);
    for (auto& b : confirmBtns)b.update(1.0f / 60.0f);
}

// Vẽ toàn bộ menu lên màn hình
void Menu::draw(sf::RenderWindow& win) {
    win.draw(bg);                                 // Vẽ nền vũ trụ trước tiên

    float centerX = win.getSize().x / 2.0f;       // Tâm ngang cửa sổ

    // Vẽ logo chính với hiệu ứng "thở"
    if (state == MAIN_MENU || state == CONFIRM_EXIT) {
        title.setCharacterSize(static_cast<unsigned>(96 * scaleY)); // Resize chữ theo cửa sổ
        centerText(title);                        // Cập nhật lại gốc tọa độ
        title.setPosition(centerX, 90 * scaleY);
        title.setOutlineThickness(4 + 0.8f * sin(animTime * 2)); // Viền nhấp nháy
        win.draw(title);
    }

    // Vẽ các nút tương ứng với trạng thái hiện tại
    if (state == MAIN_MENU)      for (auto& b : mainBtns)   b.draw(win, scaleX, scaleY);
    else if (state == MODE_SELECT) for (auto& b : modeBtns)   b.draw(win, scaleX, scaleY);
    else if (state == LEVEL_SELECT) for (auto& b : levelBtns)  b.draw(win, scaleX, scaleY);
    else if (state == HOW_TO_PLAY || state == SETTINGS) backBtn[0].draw(win, scaleX, scaleY);
    else if (state == CONFIRM_EXIT) for (auto& b : confirmBtns) b.draw(win, scaleX, scaleY);

    // Vẽ tiêu đề phụ cho từng màn hình
    sf::Text header;
    header.setFont(font);
    header.setFillColor(sf::Color(100, 230, 255));
    header.setOutlineColor(sf::Color::Cyan);
    header.setOutlineThickness(5);

    if (state == MODE_SELECT) {
        header.setString(L"CHỌN CHẾ ĐỘ CHƠI");
        header.setCharacterSize(static_cast<unsigned>(72 * scaleY));
        centerText(header);
        header.setPosition(centerX, 100 * scaleY);
        win.draw(header);
    }
    else if (state == LEVEL_SELECT) {
        header.setString(L"CHỌN ĐỘ KHÓ");
        header.setCharacterSize(static_cast<unsigned>(72 * scaleY));
        centerText(header);
        header.setPosition(centerX, 100 * scaleY);
        win.draw(header);
    }
    else if (state == SETTINGS) {
        header.setString(L"CÀI ĐẶT");
        header.setCharacterSize(static_cast<unsigned>(82 * scaleY));
        centerText(header);
        header.setPosition(centerX, 130 * scaleY);
        win.draw(header);

        sf::Text msg(L"Tính năng sẽ được cập nhật\ntrong phiên bản tiếp theo!\n\nCảm ơn bạn đã chơi <3", font,
                     static_cast<unsigned>(46 * scaleY));
        msg.setFillColor(sf::Color(200, 255, 200));
        centerText(msg);
        msg.setPosition(centerX, 330 * scaleY);
        win.draw(msg);
    }
}