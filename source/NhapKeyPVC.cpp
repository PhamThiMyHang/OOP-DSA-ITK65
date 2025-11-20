#include "../header/NhapKeyPVC.h"
#include <iostream>

// Hàm hỗ trợ để tạo texture giả cho icon người chơi (tái sử dụng từ NhapKeyPVP)
extern void createPlayerIconTexture(sf::Texture& texture); 

// Hàm hỗ trợ để tạo texture giả cho icon máy tính
void createComputerIconTexture(sf::Texture& texture) {
    sf::Image img;
    img.create(64, 64, sf::Color::Transparent);
    // Vẽ màn hình vuông đơn giản
    for(int i = 5; i < 59; ++i) {
        for(int j = 5; j < 59; ++j) {
            if (i == 5 || i == 58 || j == 5 || j == 58) img.setPixel(j,i,sf::Color::Red);
            else img.setPixel(j,i,sf::Color(10, 10, 10)); 
        }
    }
    texture.loadFromImage(img);
}

NhapKeyPVC::NhapKeyPVC(sf::Font& f, float& w, float& h, float& sx, float& sy, int levelIndex)
    : ScreenState(f, w, h, sx, sy), selectedLevel(levelIndex),
      confirmButton(L"XÁC NHẬN", f, 600, 40),
      startButton(L"BẮT ĐẦU CHƠI", f, 600, 40) // Nút bắt đầu thay thế nút xác nhận
{
    setupGameEngine(); // Khởi tạo Engine và lấy maxKeyLength

    // ... (Khởi tạo các hằng số vị trí tương tự NhapKeyPVP) ...
    float midX = winW / 2.0f;
    float colWidth = winW / 2.0f;
    float padding = 30.0f;
    float boxHeight = 150.0f;
    float inputFrameHeight = 80.0f;
    float inputBoxSize = 50.0f;
    sf::Texture playerIconTex;
    
    // --- KHU VỰC CHUNG ---

    // Khởi tạo các thành phần GUI (KeyBoxes, Frames, Text) tương tự NhapKeyPVP 
    // Vị trí của Player 1 (Left) và Player 2 (Right/Computer)

    // Khởi tạo icon
    createPlayerIconTexture(playerIconTex);
    sf::Texture computerIconTex;
    createComputerIconTexture(computerIconTex);
    
    // --- PLAYER BOXES & ICONS ---
    // Player 1 (Bên trái - Người nhập key)
    // ... (Khởi tạo playerBox1, keyInputFrame1, keyBoxes1, keyCharTexts1) ...
    playerText1.setString(L"NGƯỜI CHƠI");
    playerIcon1.setTexture(playerIconTex);
    // ... (Thiết lập vị trí) ...
    
    // Player 2 (Bên phải - Computer)
    // ... (Khởi tạo playerBox2, keyInputFrame2, keyBoxes2, keyCharTexts2) ...
    playerText2.setString(L"MÁY TÍNH");
    playerIcon2.setTexture(computerIconTex); // Sử dụng icon máy tính
    // ... (Thiết lập vị trí) ...

    // --- PROMPT TEXT & BUTTONS ---
    promptText.setFont(font);
    promptText.setCharacterSize(30);
    promptText.setFillColor(sf::Color::Yellow);
    centerText(promptText); 
    promptText.setString(L"NGƯỜI CHƠI: NHẬP CHUỖI BÍ MẬT");
    promptText.setPosition(winW / 2.0f, 100 * scaleY);
    
    // Nút BẮT ĐẦU CHƠI (cần căn chỉnh vị trí cuối cùng)
    startButton.text.setString(L"BẮT ĐẦU CHƠI");
    // ... (Căn chỉnh kích thước và vị trí cho startButton và confirmButton) ...
}

void NhapKeyPVC::setupGameEngine() {
    gameEngine = std::make_unique<NguoiQuanTro>();
    gameEngine->setMode(1); // Luôn là PvC (mode 1)
    gameEngine->chonLevel(selectedLevel + 1);
    maxKeyLength = gameEngine->getMaxLength();
    gameEngine->hamTaoCacNguoiChoi();
}

void NhapKeyPVC::resetInputDisplay() {
    // Reset chỉ khu vực nhập liệu của User 1
    currentKeyInput.clear();
    for (int i = 0; i < maxKeyLength; ++i) {
        keyCharTexts1[i].setString("");
    }
}

void NhapKeyPVC::updateKeyCharDisplays() {
    // Cập nhật các ô cho người chơi 1
    for (int i = 0; i < maxKeyLength; ++i) {
        if (i < currentKeyInput.length()) {
            keyCharTexts1[i].setString(currentKeyInput.substr(i, 1));
        } else {
            keyCharTexts1[i].setString("");
        }
        // ... (Căn giữa text trong box) ...
    }
}

GameState NhapKeyPVC::handleEvent(const sf::Vector2f& mousePos, sf::Event& e) {
    if (subState == USER_INPUT) {
        // Xử lý nhập liệu User 1 (chỉ chấp nhận số)
        if (e.type == sf::Event::TextEntered) {
            // ... (Logic nhập liệu và backspace) ...
            updateKeyCharDisplays();
        }

        // Xử lý nút XÁC NHẬN
        confirmButton.hovered = confirmButton.contains(mousePos.x, mousePos.y);

        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (confirmButton.contains(mousePos.x, mousePos.y) && currentKeyInput.length() == maxKeyLength) {
                
                // 1. Cài đặt Key của User 1
                gameEngine->KeyDoNhap(0, currentKeyInput); 
                
                // 2. Computer tạo key (sử dụng level đã chọn)
                gameEngine->generateKeyForComputer(); 

                // 3. Chuyển sang trạng thái setup máy tính
                subState = COMPUTER_SETUP;
                promptText.setString(L"MÁY TÍNH ĐÃ TẠO CHUỖI BÍ MẬT.");
                
                // 4. Hiển thị placeholder/key của máy tính (tùy theo yêu cầu)
                string computerKey = gameEngine->KeyDoComputer(); // Giả sử có hàm này
                for(int i = 0; i < maxKeyLength; ++i) {
                    keyCharTexts2[i].setString(computerKey.substr(i, 1)); // Hiển thị key
                    // ... (Căn giữa text) ...
                }
                
                // Cập nhật nút BẮT ĐẦU CHƠI
                startButton.box.setPosition(confirmButton.box.getPosition());
                startButton.text.setPosition(confirmButton.text.getPosition());
            }
        }
    } else if (subState == COMPUTER_SETUP) {
        // Xử lý nút BẮT ĐẦU CHƠI
        startButton.hovered = startButton.contains(mousePos.x, mousePos.y);
        
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (startButton.contains(mousePos.x, mousePos.y)) {
                return GAME_PVC; // Chuyển sang màn hình chơi game PvC
            }
        }
    }
    
    return NHAP_KEY_PVC;
}

void NhapKeyPVC::update(float dt) {
    if (subState == USER_INPUT) confirmButton.update(dt);
    else if (subState == COMPUTER_SETUP) startButton.update(dt);
}

void NhapKeyPVC::draw(sf::RenderWindow& win) {
    drawHeader(win, L"THIẾT LẬP CHUỖI BÍ MẬT", 80);
    win.draw(promptText);

    // Vẽ Player 1 Area (Luôn active để nhập key)
    // ... (Vẽ playerBox1, playerIcon1, playerText1, keyInputFrame1) ...
    drawKeyInputArea(win, 1);
    
    // Vẽ Player 2 Area (Computer)
    // ... (Vẽ playerBox2, playerIcon2, playerText2, keyInputFrame2) ...
    drawKeyInputArea(win, 2);

    // Vẽ nút tương ứng với trạng thái hiện tại
    if (subState == USER_INPUT) {
        confirmButton.draw(win, scaleX, scaleY);
        // Hiệu ứng Active cho khu vực nhập key
        playerBox1.setOutlineColor(sf::Color::Yellow);
        playerBox2.setOutlineColor(sf::Color(0, 200, 255));
    } else { // COMPUTER_SETUP
        startButton.draw(win, scaleX, scaleY);
        // Hiệu ứng Active cho khu vực máy tính sau khi setup xong
        playerBox1.setOutlineColor(sf::Color(0, 200, 255));
        playerBox2.setOutlineColor(sf::Color::Yellow);
    }
}

void NhapKeyPVC::drawKeyInputArea(sf::RenderWindow& win, int user) {
    // ... (Tương tự NhapKeyPVP, vẽ các KeyBoxes và Text) ...
    sf::RectangleShape* currentKeyBoxes = (user == 1) ? keyBoxes1 : keyBoxes2;
    sf::Text* currentKeyCharTexts = (user == 1) ? keyCharTexts1 : keyCharTexts2;

    for (int i = 0; i < maxKeyLength; ++i) {
        win.draw(currentKeyBoxes[i]);
        win.draw(currentKeyCharTexts[i]);
    }
}