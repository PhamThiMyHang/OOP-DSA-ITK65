// Menu.cpp – PHIÊN BẢN HOÀN HẢO NHẤT (18/11/2025)
#include "Menu.h"
// Bao gồm file header "Menu.h" đã định nghĩa lớp Menu và các thành viên của nó.
#include <iostream>
// Bao gồm thư viện nhập/xuất cơ bản (input/output), dùng cho debug (cerr, cout) nếu cần.
#include <cmath>
// Bao gồm thư viện toán học, dùng cho các hàm như sin() để tạo hiệu ứng động (animation).
#include <cstdlib>
// Bao gồm thư viện chuẩn, dùng cho hàm srand() và rand() (tạo số ngẫu nhiên).
#include <ctime>
// Bao gồm thư viện thời gian, dùng cho hàm time() để gieo mầm cho số ngẫu nhiên.

// ==================== BUTTON ====================
Menu::Button::Button(const std::wstring& s, sf::Font& f, float y, unsigned sz)
// Hàm khởi tạo (Constructor) của cấu trúc Button:
// Nhận chuỗi ký tự wide (s), font chữ (f), vị trí Y cơ sở (y) và kích thước font (sz).
 : baseY(y), baseSize(sz) {
// Danh sách khởi tạo (Initializer list): Gán giá trị y và sz cho các thành viên baseY và baseSize.
 text.setFont(f);
// Thiết lập font chữ cho đối tượng Text của nút.
 text.setString(s);
// Thiết lập nội dung (chuỗi) cho Text.
 text.setCharacterSize(sz);
// Thiết lập kích thước font chữ ban đầu.
 text.setFillColor(sf::Color::White);
// Thiết lập màu chữ là Trắng.
 text.setStyle(sf::Text::Bold);
// Thiết lập kiểu chữ là In đậm.
 text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
// Thiết lập điểm neo (origin) của Text về chính giữa văn bản (giúp căn giữa dễ hơn).

 box.setSize({720, 100});   // Nút to, dễ bấm trên điện thoại
// Thiết lập kích thước của hình chữ nhật nền (box) là 720x100.
 box.setOrigin(360, 50);
// Thiết lập điểm neo của Box về chính giữa hình chữ nhật (720/2, 100/2).
 box.setFillColor(sf::Color(20, 20, 90));
// Thiết lập màu nền của Box là xanh tím than đậm.
 box.setOutlineThickness(6);
// Thiết lập độ dày đường viền là 6 pixel.
 box.setOutlineColor(sf::Color(0, 200, 255));
// Thiết lập màu đường viền là Xanh Cyan nhạt.
}

bool Menu::Button::contains(float x, float y) const {
// Hàm kiểm tra xem tọa độ chuột (x, y) có nằm trong nút hay không.
 return box.getGlobalBounds().contains(x, y);
// Trả về true nếu tọa độ (x, y) nằm trong phạm vi hình chữ nhật của Box.
}

void Menu::Button::update(float dt) {
// Hàm cập nhật trạng thái của nút, dt là thời gian đã trôi qua (delta time), thường là 1/60 giây.
 float target = hovered ? 1.18f : 1.0f;
// Thiết lập tỷ lệ phóng to mục tiêu: 1.18f nếu chuột đang hover, 1.0f nếu không.
 float current = box.getScale().x;
// Lấy tỷ lệ phóng to hiện tại của nút (trục X).
 current += (target - current) * dt * 12.0f;
// Dùng kỹ thuật nội suy tuyến tính (Lerp) để làm mịn hiệu ứng phóng to.
 box.setScale(current, current);
// Áp dụng tỷ lệ phóng to mới cho Box.
}

void Menu::Button::draw(sf::RenderWindow& win, float sx, float sy) {
// Hàm vẽ nút, nhận cửa sổ (win) và tỷ lệ Responsive (sx, sy).
 float centerX = win.getSize().x / 2.0f;
// Tính toán tâm X của cửa sổ.
 float posY = baseY * sy;
// Tính toán vị trí Y thực tế dựa trên vị trí Y cơ sở và tỷ lệ Responsive Y (sy).

 box.setPosition(centerX, posY);
// Đặt vị trí của Box vào tâm X và vị trí Y đã tính.
 text.setPosition(centerX, posY);
// Đặt vị trí của Text vào tâm X và vị trí Y đã tính (vì origin đã được căn giữa).
 text.setCharacterSize(static_cast<unsigned>(baseSize * ((sx + sy) / 2)));
// Cập nhật kích thước chữ dựa trên kích thước cơ sở và tỷ lệ Responsive trung bình (sx+sy)/2.

 win.draw(box);
// Vẽ hình nền Box lên cửa sổ.
 win.draw(text);
// Vẽ Text lên cửa sổ (nằm trên Box).
}

// ==================== MENU ====================
void Menu::createBackground() {
// Hàm tạo hình nền tĩnh (background).
 sf::Image img;
// Khởi tạo đối tượng Image (đại diện cho dữ liệu pixel).
 img.create(900, 600, sf::Color(12, 12, 40));
// Tạo một ảnh 900x600 với màu nền xanh tím than rất đậm.
 srand(time(nullptr));
// Gieo mầm (seed) cho bộ sinh số ngẫu nhiên bằng thời gian hiện tại.
 for (int i = 0; i < 220; ++i) {
// Lặp 220 lần để vẽ các "ngôi sao" (điểm sáng).
 int x = rand() % 900, y = rand() % 600;
// Chọn ngẫu nhiên tọa độ (x, y) trong phạm vi 900x600.
 img.setPixel(x, y, sf::Color(80, 180, 255, 65));
// Đặt màu cho pixel đó là màu xanh nhạt, độ mờ (alpha) 65 (rất mờ).
 }
 bgTex.loadFromImage(img);
// Tải dữ liệu pixel từ Image vào Texture (kết cấu).
 bg.setTexture(bgTex);
// Thiết lập Texture cho Sprite (Sprite sẽ hiển thị Texture đó).
}

void Menu::recalcScale() {
// Hàm tính toán lại tỷ lệ Responsive.
 scaleX = winW / 900.0f;
// Tỷ lệ X = Chiều rộng cửa sổ hiện tại / Chiều rộng cơ sở (900).
 scaleY = winH / 600.0f;
// Tỷ lệ Y = Chiều cao cửa sổ hiện tại / Chiều cao cơ sở (600).
 bg.setScale(scaleX, scaleY);
// Phóng to/thu nhỏ hình nền Sprite theo tỷ lệ mới.
}

Menu::Menu(float w, float h) : winW(w), winH(h) {
// Hàm khởi tạo chính của lớp Menu: w, h là kích thước cửa sổ ban đầu.
 font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
// Tải font chữ từ đường dẫn cố định (cần đảm bảo font này tồn tại).
 createBackground();
// Gọi hàm tạo hình nền.
 recalcScale();
// Gọi hàm tính toán tỷ lệ ban đầu.

 title.setFont(font);
// Thiết lập font cho tiêu đề chính.
 title.setString(L"GUESS ARENA");
// Thiết lập nội dung tiêu đề.
 title.setCharacterSize(96);
// Thiết lập kích thước font tiêu đề.
 title.setFillColor(sf::Color(100, 230, 255));
// Thiết lập màu chữ.
 title.setOutlineColor(sf::Color::Cyan);
// Thiết lập màu viền chữ.
 title.setOutlineThickness(4);
// Thiết lập độ dày viền chữ.
 title.setStyle(sf::Text::Bold);
// Thiết lập kiểu chữ in đậm.

 // MENU CHÍNH
 mainBtns.emplace_back(L"BẮT ĐẦU", font, 220);
// Thêm nút "BẮT ĐẦU" vào vector mainBtns, ở vị trí Y cơ sở 220.
 mainBtns.emplace_back(L"HƯỚNG DẪN", font, 320);
 mainBtns.emplace_back(L"CÀI ĐẶT", font, 420);
 mainBtns.emplace_back(L"THOÁT", font, 520);

 // CHỌN CHẾ ĐỘ
 modeBtns.emplace_back(L"NGƯỜI VS NGƯỜI", font, 230, 56);
 modeBtns.emplace_back(L"NGƯỜI VS MÁY",  font, 330, 56);
 modeBtns.emplace_back(L"QUAY LẠI",  font, 430, 38);

 // CHỌN ĐỘ  – CÂN ĐẸP, DỄ NHÌN
 levelBtns.emplace_back(L"DỄ",  font, 200, 78);

 levelBtns.emplace_back(L"TRUNG BÌNH", font, 300, 78);

 levelBtns.emplace_back(L"KHÓ",  font, 400, 78);

 levelBtns.emplace_back(L"QUAY LẠI",  font, 500, 38);

 backBtn.emplace_back(L"QUAY LẠI MENU", font, 520, 42);
// Nút chung cho màn hình CÀI ĐẶT và HƯỚNG DẪN.
 confirmBtns.emplace_back(L"CÓ, THOÁT", font, 320, 48);
// Nút xác nhận THOÁT.
 confirmBtns.emplace_back(L"KHÔNG, Ở LẠI", font, 430, 48);
// Nút hủy THOÁT.
}

void Menu::resize(float w, float h) {
// Hàm xử lý khi cửa sổ game thay đổi kích thước.
 winW = w;
// Cập nhật chiều rộng cửa sổ hiện tại.
 winH = h;
// Cập nhật chiều cao cửa sổ hiện tại.
 recalcScale();
// Gọi hàm tính toán lại tỷ lệ Responsive.
}

void Menu::handleEvent(sf::RenderWindow& win, sf::Event& e) {
// Hàm xử lý sự kiện (chuột, phím, cuộn...).
 sf::Vector2f m = win.mapPixelToCoords(sf::Mouse::getPosition(win));
// Lấy tọa độ chuột hiện tại (đã chuyển đổi sang tọa độ thế giới/view).

 if (e.type == sf::Event::MouseMoved) {
// Nếu sự kiện là di chuyển chuột:
 auto check = [&](auto& v) { for (auto& b : v) b.hovered = b.contains(m.x, m.y); };
// Tạo một hàm lambda (hàm ẩn danh) để kiểm tra trạng thái hover cho một vector nút bất kỳ (v).
 if (state == MAIN_MENU) check(mainBtns);
// Kiểm tra hover cho Menu chính.
 else if (state == MODE_SELECT) check(modeBtns);
// Kiểm tra hover cho màn hình Chọn chế độ.
 else if (state == LEVEL_SELECT) check(levelBtns);
 else if (state == CONFIRM_EXIT) check(confirmBtns);
 else check(backBtn);
// Các màn hình còn lại (HOW_TO_PLAY, SETTINGS) chỉ cần kiểm tra nút backBtn.
 }

 if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
// Nếu sự kiện là nhấn chuột trái:
 if (state == MAIN_MENU) {
// Xử lý click trong Menu chính:
  if (mainBtns[0].contains(m.x, m.y)) state = MODE_SELECT;
// Nếu click vào nút 0 (BẮT ĐẦU), chuyển sang trạng thái MODE_SELECT.
  if (mainBtns[1].contains(m.x, m.y)) state = HOW_TO_PLAY;
  if (mainBtns[2].contains(m.x, m.y)) state = SETTINGS;
  if (mainBtns[3].contains(m.x, m.y)) state = CONFIRM_EXIT;
 }
 else if (state == MODE_SELECT) {
// Xử lý click trong Chọn chế độ:
  if (modeBtns[0].contains(m.x, m.y)) { pvp = true;  state = LEVEL_SELECT; }
// Nếu chọn PvP, đặt cờ pvp=true và chuyển sang LEVEL_SELECT.
  if (modeBtns[1].contains(m.x, m.y)) { pvp = false; state = LEVEL_SELECT; }
// Nếu chọn PvC, đặt cờ pvp=false và chuyển sang LEVEL_SELECT.
  if (modeBtns[2].contains(m.x, m.y)) state = MAIN_MENU;
// Nếu click "QUAY LẠI", chuyển về MAIN_MENU.
 }
 else if (state == LEVEL_SELECT) {
// Xử lý click trong Chọn độ khó:
  if (levelBtns[0].contains(m.x, m.y)) { level = 0; state = pvp ? GAME_PVP : GAME_PVC; }
// Nếu chọn DỄ (level=0), chuyển sang trạng thái chơi game (PvP hoặc PvC tùy pvp).
  if (levelBtns[1].contains(m.x, m.y)) { level = 1; state = pvp ? GAME_PVP : GAME_PVC; }
// Nếu chọn TRUNG BÌNH (level=1).
  if (levelBtns[2].contains(m.x, m.y)) { level = 2; state = pvp ? GAME_PVP : GAME_PVC; }
// Nếu chọn KHÓ (level=2).
  if (levelBtns[3].contains(m.x, m.y)) state = MODE_SELECT;
// Nếu click "QUAY LẠI", chuyển về MODE_SELECT.
 }
 else if (state == SETTINGS || state == HOW_TO_PLAY) {
// Xử lý click trong CÀI ĐẶT và HƯỚNG DẪN:
  if (backBtn[0].contains(m.x, m.y)) state = MAIN_MENU;
// Nếu click nút "QUAY LẠI MENU", chuyển về MAIN_MENU.
 }
 else if (state == CONFIRM_EXIT) {
// Xử lý click trong Xác nhận thoát:
  if (confirmBtns[0].contains(m.x, m.y)) win.close();
// Nếu click "CÓ, THOÁT", đóng cửa sổ game.
  if (confirmBtns[1].contains(m.x, m.y)) state = MAIN_MENU;
// Nếu click "KHÔNG, Ở LẠI", chuyển về MAIN_MENU.
 }
 }

 if (state == HOW_TO_PLAY && e.type == sf::Event::MouseWheelScrolled)
// Nếu đang ở màn hình HƯỚNG DẪN và có sự kiện cuộn chuột.
 scrollOffset += e.mouseWheelScroll.delta * 70;
// Cập nhật độ lệch cuộn: delta là hướng cuộn, nhân 70 để tăng tốc độ cuộn.
}

void Menu::update() {
// Hàm cập nhật logic game (không liên quan đến sự kiện).
 animTime += 1.0f / 60.0f;
// Tăng biến thời gian animation lên 1/60 giây (giả sử FPS là 60).
 for (auto& b : mainBtns)  b.update(1.0f / 60.0f);
// Cập nhật hiệu ứng cho từng nút trong mainBtns.
 for (auto& b : modeBtns)  b.update(1.0f / 60.0f);
// ... và các vector nút khác.
 for (auto& b : levelBtns)  b.update(1.0f / 60.0f);
 for (auto& b : backBtn)  b.update(1.0f / 60.0f);
 for (auto& b : confirmBtns)b.update(1.0f / 60.0f);
}

void Menu::draw(sf::RenderWindow& win) {
// Hàm vẽ giao diện lên cửa sổ.
 win.draw(bg);
// Vẽ hình nền.

 float centerX = win.getSize().x / 2.0f;
// Tính toán lại tâm X của cửa sổ.

 // Logo chính
 if (state == MAIN_MENU || state == CONFIRM_EXIT) {
// Chỉ vẽ Logo nếu đang ở Menu chính hoặc Xác nhận thoát.
 title.setCharacterSize(static_cast<unsigned>(96 * scaleY));
// Điều chỉnh kích thước font của Logo theo tỷ lệ Responsive Y (scaleY).
 title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
// Căn giữa Text (cần gọi lại vì kích thước chữ thay đổi có thể làm thay đổi kích thước bounding box).
 title.setPosition(centerX, 90 * scaleY);
// Đặt vị trí Logo (Y cơ sở 90, có tính Responsive).
 title.setOutlineThickness(4 + 0.8f * sin(animTime * 2));
// Tạo hiệu ứng viền chữ "thở" (pulsing effect) bằng hàm sin().
 win.draw(title);
// Vẽ Logo.
 }

 // Vẽ nút
 if (state == MAIN_MENU)  for (auto& b : mainBtns)  b.draw(win, scaleX, scaleY);
// Nếu Menu chính, vẽ các nút mainBtns.
 else if (state == MODE_SELECT)  for (auto& b : modeBtns)  b.draw(win, scaleX, scaleY);
 else if (state == LEVEL_SELECT)  for (auto& b : levelBtns)  b.draw(win, scaleX, scaleY);
 else if (state == HOW_TO_PLAY || state == SETTINGS) backBtn[0].draw(win, scaleX, scaleY);
// Nếu HƯỚNG DẪN hoặc CÀI ĐẶT, chỉ vẽ nút "QUAY LẠI MENU" (chỉ có 1 nút trong backBtn).
 else if (state == CONFIRM_EXIT)  for (auto& b : confirmBtns) b.draw(win, scaleX, scaleY);

 // Tiêu đề phụ
 sf::Text header;
// Khởi tạo đối tượng Text cho tiêu đề phụ (HEADER).
 header.setFont(font);
 header.setFillColor(sf::Color(100, 230, 255));
 header.setOutlineThickness(5);
 header.setOutlineColor(sf::Color::Cyan);
 header.setOrigin(header.getLocalBounds().width / 2, header.getLocalBounds().height / 2);
 header.setPosition(centerX, 100 * scaleY);
// Thiết lập vị trí Header (Y cơ sở 100).

 if (state == MODE_SELECT) {
// Nếu đang ở màn hình Chọn chế độ:
 if (state == MODE_SELECT) {
    header.setString(L"CHỌN CHẾ ĐỘ CHƠI");
    header.setCharacterSize(static_cast<unsigned>(72 * scaleY));

    header.setOrigin(header.getLocalBounds().width / 2, 
                     header.getLocalBounds().height / 2);
    header.setPosition(centerX, 100 * scaleY);

    win.draw(header);
}
// Điều chỉnh kích thước font.
// Vẽ Header.
 }
 else if (state == LEVEL_SELECT) {
// Nếu đang ở màn hình Chọn độ khó:
 header.setString(L"CHỌN ĐỘ KHÓ");
    header.setCharacterSize(static_cast<unsigned>(72 * scaleY));

    header.setOrigin(header.getLocalBounds().width / 2, 
                     header.getLocalBounds().height / 2);
    header.setPosition(centerX, 100 * scaleY);

    win.draw(header);
 }
 else if (state == SETTINGS) {
// Nếu đang ở màn hình Cài đặt:
  header.setString(L"CÀI ĐẶT");
    header.setCharacterSize(static_cast<unsigned>(82 * scaleY));

    header.setOrigin(header.getLocalBounds().width / 2, 
                     header.getLocalBounds().height / 2);
    header.setPosition(centerX, 130 * scaleY);

    win.draw(header);

 sf::Text msg(L"Tính năng sẽ được cập nhật\ntrong phiên bản tiếp theo!\n\nCảm ơn bạn đã chơi <3", font,
// Tạo thông báo cho màn hình Cài đặt (chưa có tính năng).
   static_cast<unsigned>(46 * scaleY));
// Thiết lập kích thước font.
 msg.setFillColor(sf::Color(200, 255, 200));
 msg.setOrigin(msg.getLocalBounds().width / 2, msg.getLocalBounds().height / 2);
msg.setPosition(centerX, 330 * scaleY);
// Đặt vị trí thông báo (Y cơ sở 330).
win.draw(msg);
// Vẽ thông báo.
}
}