#include "../header/NhapKeyPVP.h"
#include <iostream>

// Hàm hỗ trợ để lấy một texture giả cho icon người chơi
// Trong thực tế, bạn sẽ tải một file hình ảnh thực sự.
void createPlayerIconTexture(sf::Texture& texture) {
    sf::Image img;
    img.create(64, 64, sf::Color::Transparent);
    // Vẽ một hình người đơn giản
    for(int i = 0; i < 64; ++i) {
        for(int j = 0; j < 64; ++j) {
            if (j > 20 && j < 44 && i > 10 && i < 20) img.setPixel(j,i,sf::Color::White); // Đầu
            if (j > 28 && j < 36 && i > 20 && i < 40) img.setPixel(j,i,sf::Color::White); // Thân
            if (j > 20 && j < 44 && i > 40 && i < 50) img.setPixel(j,i,sf::Color::White); // Chân
        }
    }
    texture.loadFromImage(img);
}

NhapKeyPVP::NhapKeyPVP(sf::Font& f, float& w, float& h, float& sx, float& sy, int levelIndex)
    : ScreenState(f, w, h, sx, sy), selectedLevel(levelIndex),
      confirmButton(L"XÁC NHẬN", f, 600, 40) // Nút xác nhận ở dưới
{
    // 1. Cấu hình Engine để lấy maxKeyLength
    setupGameEngine();

    // 2. Khởi tạo GUI Components dựa trên hình ảnh
    float midX = winW / 2.0f;
    float colWidth = winW / 2.0f; // Mỗi người chơi chiếm 1 nửa màn hình
    float padding = 30.0f;
    float boxHeight = 150.0f; // Chiều cao của khung Player box
    float inputFrameHeight = 80.0f; // Chiều cao của khung nhập key
    float inputBoxSize = 50.0f; // Kích thước mỗi ô ký tự

    // --- PLAYER BOXES (PLAYER 1 & PLAYER 2) ---
    // Player 1 (Bên trái)
    playerBox1.setSize(sf::Vector2f(colWidth - padding * 2, boxHeight));
    playerBox1.setFillColor(sf::Color(20, 20, 40, 180)); // Nền tối trong suốt
    playerBox1.setOutlineThickness(2);
    playerBox1.setOutlineColor(sf::Color(0, 200, 255));
    playerBox1.setPosition(padding, winH - boxHeight - padding); // Dưới cùng bên trái

    playerText1.setFont(font);
    playerText1.setString(L"PLAYER 1");
    playerText1.setCharacterSize(30);
    playerText1.setFillColor(sf::Color::White);
    centerText(playerText1);
    playerText1.setPosition(playerBox1.getPosition().x + playerBox1.getSize().x / 2.0f, playerBox1.getPosition().y + 100);

    createPlayerIconTexture(playerIconTex); // Tạo texture giả
    playerIcon1.setTexture(playerIconTex);
    playerIcon1.setScale(1.0f, 1.0f);
    playerIcon1.setPosition(playerBox1.getPosition().x + playerBox1.getSize().x / 2.0f - playerIcon1.getGlobalBounds().width / 2.0f, playerBox1.getPosition().y + 20);

    // Player 2 (Bên phải) - Tương tự Player 1
    playerBox2.setSize(sf::Vector2f(colWidth - padding * 2, boxHeight));
    playerBox2.setFillColor(sf::Color(20, 20, 40, 180));
    playerBox2.setOutlineThickness(2);
    playerBox2.setOutlineColor(sf::Color(0, 200, 255));
    playerBox2.setPosition(midX + padding, winH - boxHeight - padding);

    playerText2.setFont(font);
    playerText2.setString(L"PLAYER 2");
    playerText2.setCharacterSize(30);
    playerText2.setFillColor(sf::Color::White);
    centerText(playerText2);
    playerText2.setPosition(playerBox2.getPosition().x + playerBox2.getSize().x / 2.0f, playerBox2.getPosition().y + 100);

    playerIcon2.setTexture(playerIconTex);
    playerIcon2.setScale(1.0f, 1.0f);
    playerIcon2.setPosition(playerBox2.getPosition().x + playerBox2.getSize().x / 2.0f - playerIcon2.getGlobalBounds().width / 2.0f, playerBox2.getPosition().y + 20);


    // --- KEY INPUT FRAMES (HAND) ---
    // Frame cho Player 1
    keyInputFrame1.setSize(sf::Vector2f(maxKeyLength * (inputBoxSize + 10) + 10, inputFrameHeight));
    keyInputFrame1.setFillColor(sf::Color(30, 30, 60, 180));
    keyInputFrame1.setOutlineThickness(1);
    keyInputFrame1.setOutlineColor(sf::Color(100, 100, 200));
    keyInputFrame1.setPosition(playerBox1.getPosition().x, playerBox1.getPosition().y - inputFrameHeight - padding);

    // Frame cho Player 2
    keyInputFrame2.setSize(sf::Vector2f(maxKeyLength * (inputBoxSize + 10) + 10, inputFrameHeight));
    keyInputFrame2.setFillColor(sf::Color(30, 30, 60, 180));
    keyInputFrame2.setOutlineThickness(1);
    keyInputFrame2.setOutlineColor(sf::Color(100, 100, 200));
    keyInputFrame2.setPosition(playerBox2.getPosition().x, playerBox2.getPosition().y - inputFrameHeight - padding);

    // --- KEY BOXES & TEXTS ---
    // Tính toán vị trí bắt đầu cho các ô ký tự
    float startX1 = keyInputFrame1.getPosition().x + 5;
    float startX2 = keyInputFrame2.getPosition().x + 5;
    float boxY = keyInputFrame1.getPosition().y + (inputFrameHeight - inputBoxSize) / 2.0f; // Căn giữa chiều cao

    for (int i = 0; i < maxKeyLength; ++i) {
        // Player 1 Key Boxes
        keyBoxes1[i].setSize(sf::Vector2f(inputBoxSize, inputBoxSize));
        keyBoxes1[i].setFillColor(sf::Color(50, 50, 80));
        keyBoxes1[i].setOutlineThickness(1);
        keyBoxes1[i].setOutlineColor(sf::Color(150, 150, 250));
        keyBoxes1[i].setPosition(startX1 + i * (inputBoxSize + 10), boxY);

        keyCharTexts1[i].setFont(font);
        keyCharTexts1[i].setCharacterSize(inputBoxSize * 0.6f);
        keyCharTexts1[i].setFillColor(sf::Color::White);
        centerText(keyCharTexts1[i]); // Căn giữa sau khi setString

        // Player 2 Key Boxes
        keyBoxes2[i].setSize(sf::Vector2f(inputBoxSize, inputBoxSize));
        keyBoxes2[i].setFillColor(sf::Color(50, 50, 80));
        keyBoxes2[i].setOutlineThickness(1);
        keyBoxes2[i].setOutlineColor(sf::Color(150, 150, 250));
        keyBoxes2[i].setPosition(startX2 + i * (inputBoxSize + 10), boxY);

        keyCharTexts2[i].setFont(font);
        keyCharTexts2[i].setCharacterSize(inputBoxSize * 0.6f);
        keyCharTexts2[i].setFillColor(sf::Color::White);
        centerText(keyCharTexts2[i]); // Căn giữa sau khi setString
    }

    // --- PROMPT TEXT ---
    promptText.setFont(font);
    promptText.setCharacterSize(30);
    promptText.setFillColor(sf::Color::Yellow);
    centerText(promptText); // Sẽ được cập nhật trong hàm draw/handleEvent

    // --- CONFIRM BUTTON ---
    confirmButton.text.setString(L"XÁC NHẬN");
    confirmButton.box.setSize({200, 60}); // Kích thước nhỏ hơn
    confirmButton.box.setOrigin(100, 30);      // Thiết lập origin cho hình chữ nhật nền
    confirmButton.text.setOrigin(100, 30);
    confirmButton.text.setCharacterSize(30);
    centerText(confirmButton.text);
    confirmButton.box.setPosition(winW / 2.0f, 600 * scaleY); // Vị trí cuối cùng
    confirmButton.text.setPosition(winW / 2.0f, 600 * scaleY);

    // Cập nhật trạng thái hiển thị ban đầu
    promptText.setString(L"NGƯỜI CHƠI 1: NHẬP CHUỖI BÍ MẬT");
    promptText.setPosition(winW / 2.0f, 100 * scaleY); // Đầu màn hình
}

void NhapKeyPVP::setupGameEngine() {
    gameEngine = std::make_unique<NguoiQuanTro>();
    gameEngine->setMode(2); // Luôn là PvP (mode 2)
    gameEngine->chonLevel(selectedLevel + 1);
    this->maxKeyLength = gameEngine->getMaxLength();
    gameEngine->hamTaoCacNguoiChoi() ;// Đặt tên người chơi
}

void NhapKeyPVP::resetInputDisplay(int user) {
    currentKeyInput.clear();
    for (int i = 0; i < maxKeyLength; ++i) {
        if (user == 1) keyCharTexts1[i].setString("");
        else keyCharTexts2[i].setString("");
    }
}

void NhapKeyPVP::updateKeyCharDisplays() {
    // Cập nhật các ô cho người chơi hiện tại
    sf::Text* currentKeyCharTexts = (currentInputUser == 1) ? keyCharTexts1 : keyCharTexts2;
    sf::RectangleShape* currentKeyBoxes = (currentInputUser == 1) ? keyBoxes1 : keyBoxes2;

    for (int i = 0; i < maxKeyLength; ++i) {
        if (i < currentKeyInput.length()) {
            currentKeyCharTexts[i].setString(currentKeyInput.substr(i, 1));
        } else {
            currentKeyCharTexts[i].setString("");
        }
        // Căn giữa văn bản trong ô
        centerText(currentKeyCharTexts[i]);
        currentKeyCharTexts[i].setPosition(
            currentKeyBoxes[i].getPosition().x + currentKeyBoxes[i].getSize().x / 2.0f,
            currentKeyBoxes[i].getPosition().y + currentKeyBoxes[i].getSize().y / 2.0f
        );
    }
}


GameState NhapKeyPVP::handleEvent(const sf::Vector2f& mousePos, sf::Event& e) {
    if(selectedLevel + 1 == 1){
        if (e.type == sf::Event::TextEntered) {
            if (e.text.unicode >= 48 && e.text.unicode <= 57) { // Chỉ chấp nhận số từ '0' - '9'
                if (currentKeyInput.length() < maxKeyLength) {
                    currentKeyInput += static_cast<char>(e.text.unicode);
                    updateKeyCharDisplays();
                }
            } else if (e.text.unicode == 8) { // Backspace
                if (!currentKeyInput.empty()) {
                    currentKeyInput.pop_back();
                    updateKeyCharDisplays();
                }
            }
        }
    }else if(selectedLevel + 1 == 2){
        if (e.type == sf::Event::TextEntered) {
            if (e.text.unicode >= 97 && e.text.unicode <= 129) { // Chỉ chấp nhận số từ '0' - '9'
                if (currentKeyInput.length() < maxKeyLength) {
                    currentKeyInput += static_cast<char>(e.text.unicode);
                    updateKeyCharDisplays();
                }
            } else if (e.text.unicode == 8) { // Backspace
                if (!currentKeyInput.empty()) {
                    currentKeyInput.pop_back();
                    updateKeyCharDisplays();
                }
            }
        }
    }else{
        if ((e.text.unicode >= 97 && e.text.unicode <= 129) ||(e.text.unicode >= 48 && e.text.unicode <= 57)){
             if (currentKeyInput.length() < maxKeyLength) {
                    currentKeyInput += static_cast<char>(e.text.unicode);
                    updateKeyCharDisplays();
                }
        }else if (e.text.unicode == 8) { // Backspace
                if (!currentKeyInput.empty()) {
                    currentKeyInput.pop_back();
                    updateKeyCharDisplays();
                }
            }
    }
    

    // Xử lý nút Xác nhận
    confirmButton.hovered = confirmButton.contains(mousePos.x, mousePos.y);

    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
        if (confirmButton.contains(mousePos.x, mousePos.y)) {
            // Kiểm tra độ dài key đã đủ chưa
            if (currentKeyInput.length() != maxKeyLength) {
                // Có thể hiển thị thông báo lỗi GUI ở đây
                std::cout << "Key phải đủ " << maxKeyLength << " ký tự!\n";
                return NHAP_KEY_PVP;
            }

            // Kiểm tra key hợp lệ theo quy định của NguoiQuanTro (ví dụ: không trùng số)
            // (Cần bổ sung hàm kiểm tra vào NguoiQuanTro/Level nếu chưa có)
            // Ví dụ: if (!gameEngine->isValidKey(currentKeyInput)) { ... return NHAP_KEY_PVP; }

            if (currentInputUser == 1) {
                keyUser1_set = currentKeyInput; // Lưu key của User 1
                gameEngine->KeyDoNhap(currentInputUser-1,currentKeyInput); // Cài đặt vào engine
                currentInputUser = 2; // Chuyển sang User 2
                promptText.setString(L"NGƯỜI CHƠI 2: NHẬP CHUỖI BÍ MẬT");
                centerText(promptText);
                resetInputDisplay(currentInputUser); // Reset input cho người chơi mới
            } else if (currentInputUser == 2) {
                keyUser2_set = currentKeyInput; // Lưu key của User 2
                gameEngine->KeyDoNhap(1, keyUser2_set); // Cài đặt vào engine
                // Cả hai người chơi đã nhập key, chuyển sang màn hình GAME_PVP
                return GAME_PVP;
            }
        }
    }

    return NHAP_KEY_PVP; // Giữ nguyên trạng thái nhập key
}

void NhapKeyPVP::update(float dt) {
    confirmButton.update(dt);
    // Có thể thêm hiệu ứng nhấp nháy cho ô nhập hiện tại
}

void NhapKeyPVP::draw(sf::RenderWindow& win) {
    drawHeader(win, L"THIẾT LẬP CHUỖI BÍ MẬT", 80); // Tiêu đề chung
    win.draw(promptText); // Nhắc nhở người chơi hiện tại

    // Vẽ Player 1 Area
    win.draw(playerBox1);
    win.draw(playerIcon1);
    win.draw(playerText1);
    win.draw(keyInputFrame1);
    drawKeyInputArea(win, 1);

    // Vẽ Player 2 Area
    win.draw(playerBox2);
    win.draw(playerIcon2);
    win.draw(playerText2);
    win.draw(keyInputFrame2);
    drawKeyInputArea(win, 2);

    // Hiệu ứng "active" cho khu vực người chơi đang nhập
    if (currentInputUser == 1) {
        playerBox1.setOutlineColor(sf::Color::Yellow);
        playerBox2.setOutlineColor(sf::Color(0, 200, 255));
    } else {
        playerBox1.setOutlineColor(sf::Color(0, 200, 255));
        playerBox2.setOutlineColor(sf::Color::Yellow);
    }
    
    confirmButton.draw(win, scaleX, scaleY);
}

void NhapKeyPVP::drawKeyInputArea(sf::RenderWindow& win, int user) {
    sf::RectangleShape* currentKeyBoxes = (user == 1) ? keyBoxes1 : keyBoxes2;
    sf::Text* currentKeyCharTexts = (user == 1) ? keyCharTexts1 : keyCharTexts2;

    for (int i = 0; i < maxKeyLength; ++i) {
        win.draw(currentKeyBoxes[i]);
        win.draw(currentKeyCharTexts[i]);
    }
}