#include "../header/GamePVP.h"
#include <iostream>
#include <algorithm> // Dùng cho std::min và std::fill

// Hàm helper để căn giữa Text (Giả định được định nghĩa trong ScreenState hoặc Menu.h)
extern void centerText(sf::Text& txt); 

// === HÀM HỖ TRỢ KHỞI TẠO GUI ĐẦY ĐỦ ===
void GamePVP::initializeGUI() {
    // --- Khởi tạo maxKeyLength ---
    if (gameEngine) maxKeyLength = gameEngine->getMaxLength();
    else maxKeyLength = 4; // Giá trị mặc định nếu lỗi
    
    // --- CÁC HẰNG SỐ VỊ TRÍ & KÍCH THƯỚC ---
    float colWidth = winW / 2.0f;
    float padding = 20.0f;
    float scale = std::min(scaleX, scaleY); // Dùng scale nhỏ hơn để đảm bảo tỷ lệ

    float startX1 = padding; 
    float startX2 = colWidth + padding;
    
    // Kích thước/Vị trí Buttons (A B C D...)
    float buttonSize = 50.0f * scale;
    float startYButtons = 550.0f * scaleY; 
    
    // Kích thước/Vị trí Input Box (HAND)
    float inputFrameY = 350.0f * scaleY;
    float inputBoxSize = 40.0f * scale;
    
    // Kích thước/Vị trí Guess Grid và Result Lights
    float gridStartX1 = startX1 + 10;
    float gridStartX2 = startX2 + 10;
    float gridStartY = 100.0f * scaleY; 
    float gridBoxSize = 30.0f * scale;
    float lightSize = 10.0f * scale; 
    
    // Kích thước/Vị trí Hearts và Hint Lights
    float heartsStartY = 50.0f * scaleY;
    float heartSize = 25.0f * scale; 
    float hintLightSize = 30.0f * scale;
    float hintLightY = winH - 100 * scaleY;

    // --- Nút Ký tự (A B C D...) ---
    char baseChar = 'A'; // Ký tự bắt đầu cho P1
    char baseChar2 = 'H'; // Ký tự bắt đầu cho P2 (Giả định)
    
    for (int i = 0; i < maxKeyLength; ++i) { 
        // User 1 Buttons (Left)
        keyButtons1[i].setSize(sf::Vector2f(buttonSize, buttonSize));
        keyButtons1[i].setFillColor(sf::Color(50, 150, 255));
        keyButtons1[i].setPosition(startX1 + 40 + i * (buttonSize + 10), startYButtons);
        
        keyButtonTexts1[i].setFont(font);
        keyButtonTexts1[i].setCharacterSize(30 * scaleY);
        keyButtonTexts1[i].setFillColor(sf::Color::White);
        keyButtonTexts1[i].setString(static_cast<char>(baseChar + i)); 
        centerText(keyButtonTexts1[i]);
        keyButtonTexts1[i].setPosition(keyButtons1[i].getPosition().x + buttonSize/2, keyButtons1[i].getPosition().y + buttonSize/2 - 5);

        // User 2 Buttons (Right)
        keyButtons2[i].setSize(sf::Vector2f(buttonSize, buttonSize));
        keyButtons2[i].setFillColor(sf::Color(255, 100, 50));
        keyButtons2[i].setPosition(startX2 + 40 + i * (buttonSize + 10), startYButtons);
        
        keyButtonTexts2[i].setFont(font);
        keyButtonTexts2[i].setCharacterSize(30 * scaleY);
        keyButtonTexts2[i].setFillColor(sf::Color::White);
        keyButtonTexts2[i].setString(static_cast<char>(baseChar2 + i));
        centerText(keyButtonTexts2[i]);
        keyButtonTexts2[i].setPosition(keyButtons2[i].getPosition().x + buttonSize/2, keyButtonTexts2[i].getPosition().y + buttonSize/2 - 5);
    }
    
    // --- Ô nhập liệu hiện tại (HAND) ---
    for (int i = 0; i < maxKeyLength; ++i) {
        // User 1
        inputBoxes1[i].setSize(sf::Vector2f(inputBoxSize, inputBoxSize));
        inputBoxes1[i].setFillColor(sf::Color(50, 50, 80));
        inputBoxes1[i].setOutlineThickness(1);
        inputBoxes1[i].setOutlineColor(sf::Color::White);
        inputBoxes1[i].setPosition(startX1 + 100 + i * (inputBoxSize + 10), inputFrameY);

        inputTexts1[i].setFont(font);
        inputTexts1[i].setCharacterSize(30 * scaleY);
        inputTexts1[i].setFillColor(sf::Color::White);

        // User 2
        inputBoxes2[i].setSize(sf::Vector2f(inputBoxSize, inputBoxSize));
        inputBoxes2[i].setFillColor(sf::Color(50, 50, 80));
        inputBoxes2[i].setOutlineThickness(1);
        inputBoxes2[i].setOutlineColor(sf::Color::White);
        inputBoxes2[i].setPosition(startX2 + 100 + i * (inputBoxSize + 10), inputFrameY);

        inputTexts2[i].setFont(font);
        inputTexts2[i].setCharacterSize(30 * scaleY);
        inputTexts2[i].setFillColor(sf::Color::White);
    }

    // --- Lịch sử đoán (Guess Grid) và Kết quả (Result Lights) ---
    for (int r = 0; r < maxTurns; ++r) { 
        for (int c = 0; c < maxKeyLength; ++c) {
            // Grid Box
            guessGrid1[r][c].setSize(sf::Vector2f(gridBoxSize, gridBoxSize));
            guessGrid1[r][c].setFillColor(sf::Color(30, 30, 30));
            guessGrid1[r][c].setOutlineThickness(1);
            guessGrid1[r][c].setOutlineColor(sf::Color(70, 70, 70));
            guessGrid1[r][c].setPosition(gridStartX1 + c * (gridBoxSize + 5), gridStartY + r * (gridBoxSize + 10));

            guessGrid2[r][c].setSize(sf::Vector2f(gridBoxSize, gridBoxSize));
            guessGrid2[r][c].setFillColor(sf::Color(30, 30, 30));
            guessGrid2[r][c].setOutlineThickness(1);
            guessGrid2[r][c].setOutlineColor(sf::Color(70, 70, 70));
            guessGrid2[r][c].setPosition(gridStartX2 + c * (gridBoxSize + 5), gridStartY + r * (gridBoxSize + 10));
        }

        // Result Lights 
        for (int l = 0; l < 2; ++l) {
            // Player 1
            resultLights1[r][l].setSize(sf::Vector2f(lightSize, lightSize));
            resultLights1[r][l].setFillColor(sf::Color::Black);
            resultLights1[r][l].setPosition(gridStartX1 + maxKeyLength * (gridBoxSize + 5) + 10 + l * (lightSize + 5), 
                                            gridStartY + r * (gridBoxSize + 10) + gridBoxSize / 2.0f);

            // Player 2
            resultLights2[r][l].setSize(sf::Vector2f(lightSize, lightSize));
            resultLights2[r][l].setFillColor(sf::Color::Black);
            resultLights2[r][l].setPosition(gridStartX2 + maxKeyLength * (gridBoxSize + 5) + 10 + l * (lightSize + 5), 
                                            gridStartY + r * (gridBoxSize + 10) + gridBoxSize / 2.0f);
        }
    }
    
    // --- Trái tim (Hearts) ---
    float heartsStartX = startX1 + 10;
    for (int i = 0; i < 5; ++i) { // 5 Hearts
        hearts1[i].setSize(sf::Vector2f(heartSize, heartSize));
        hearts1[i].setFillColor(sf::Color::Red);
        hearts1[i].setPosition(heartsStartX + i * (heartSize + 5), heartsStartY);

        hearts2[i].setSize(sf::Vector2f(heartSize, heartSize));
        hearts2[i].setFillColor(sf::Color::Red);
        hearts2[i].setPosition(startX2 + 10 + i * (heartSize + 5), heartsStartY);
    }

    // --- Bóng đèn gợi ý (Hint Lights) ---
    hintLights1[0].setRadius(hintLightSize / 2.0f); hintLights1[0].setFillColor(sf::Color::Yellow); hintLights1[0].setPosition(startX1 + 50, hintLightY); 
    hintLights1[1].setRadius(hintLightSize / 2.0f); hintLights1[1].setFillColor(sf::Color::White); hintLights1[1].setPosition(startX1 + 50 + hintLightSize + 10, hintLightY);

    hintLights2[0].setRadius(hintLightSize / 2.0f); hintLights2[0].setFillColor(sf::Color::Yellow); hintLights2[0].setPosition(startX2 + 50, hintLightY); 
    hintLights2[1].setRadius(hintLightSize / 2.0f); hintLights2[1].setFillColor(sf::Color::White); hintLights2[1].setPosition(startX2 + 50 + hintLightSize + 10, hintLightY);

    // --- Nút Đoán (GUESS) ---
    guessButton.box.setSize({150 * scaleX, 50 * scaleY});
    guessButton.box.setOrigin(75 * scaleX, 25 * scaleY);
    guessButton.box.setPosition(winW / 2.0f, 650 * scaleY);
    guessButton.text.setOrigin(75 * scaleX, 25 * scaleY);
    guessButton.text.setPosition(winW / 2.0f, 650 * scaleY);
    guessButton.text.setCharacterSize(30 * scaleY);
}


// KHÔNG SỬA ĐỔI: Constructor của bạn được giữ nguyên
GamePVP::GamePVP(sf::Font& f, float& w, float& h, float& sx, float& sy, std::unique_ptr<NguoiQuanTro> engine)
    : ScreenState(f, w, h, sx, sy), 
      gameEngine(std::move(engine)),
      guessButton(L"ĐOÁN", f, 500, 40) 
{
    initializeGUI();
    user1Guesses.reserve(maxTurns);
    user2Guesses.reserve(maxTurns);
    inputKeyStatus.fill(0); 
}

// Sửa lỗi căn giữa/vị trí text trong ô nhập liệu
void GamePVP::updateInputDisplay(int playerID) {
    sf::Text* currentInputTexts = (playerID == 1) ? inputTexts1 : inputTexts2;
    sf::RectangleShape* currentInputBoxes = (playerID == 1) ? inputBoxes1 : inputBoxes2;

    for (int i = 0; i < maxKeyLength; ++i) {
        if (i < currentInput.length()) {
            currentInputTexts[i].setString(currentInput.substr(i, 1));
        } else {
            currentInputTexts[i].setString("");
        }
        // THÊM: Căn giữa và đặt vị trí text
        centerText(currentInputTexts[i]);
        currentInputTexts[i].setPosition(
            currentInputBoxes[i].getPosition().x + currentInputBoxes[i].getSize().x / 2.0f,
            currentInputBoxes[i].getPosition().y + currentInputBoxes[i].getSize().y / 2.0f - 5 
        );
    }
}

// Sửa lỗi thiếu tham số 'currentInput' trong checkKey
void GamePVP::processGuess(int playerID) {
    if (currentInput.length() != maxKeyLength) return;

    int opponentID = (playerID == 1) ? 2 : 1;
    
    GuessRecord record;
    record.guess = currentInput;
    int a[maxKeyLength];
    std::fill(a, a + maxKeyLength, 0); // Đảm bảo mảng a được khởi tạo 0

    int mode = gameEngine->getMode();
    // SỬA LỖI: Bổ sung tham số 'currentInput' cho hàm checkKey
    int sokytudung = gameEngine->checkKey(playerID, mode, a); 
    
    for(int i=0; i<maxKeyLength;i++){
        record.matchStatus[i] = a[i];
    }
    if (playerID == 1) user1Guesses.push_back(record);
    else user2Guesses.push_back(record);

    if (sokytudung == maxKeyLength) {
        isGameOver = true;
        gameEngine->setWinner(playerID);
        return;
    }
    
    currentInput.clear();
    switchPlayer();
}

// KHÔNG SỬA ĐỔI: Logic switchPlayer của bạn được giữ nguyên
void GamePVP::switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
    currentTurn = (currentPlayer == 1) ? currentTurn : currentTurn + 1;
}

// Sửa lỗi cú pháp và logic lặp lại trong handleEvent
GameState GamePVP::handleEvent(const sf::Vector2f& mousePos, sf::Event& e) {
    if (isGameOver) return GAME_PVP;
    
    int level = gameEngine->getIDlevel();
    
    if (e.type == sf::Event::TextEntered) {
        char inputChar = static_cast<char>(e.text.unicode);
        
        // Backspace
        if (e.text.unicode == 8) { 
            if (!currentInput.empty()) {
                currentInput.pop_back();
                updateInputDisplay(currentPlayer);
            }
        } 
        // Logic nhập liệu theo Level (Đã sửa lỗi cú pháp, loại bỏ lặp lại và thiếu })
        else {
            bool isValidChar = false;
            
            // Chuyển đổi sang chữ thường để kiểm tra, giữ nguyên chữ hoa nếu cần
            if (inputChar >= 'A' && inputChar <= 'Z') inputChar += 32; // Chuyển sang chữ thường

            if (level == 1 && (inputChar >= '0' && inputChar <= '9')) { isValidChar = true; } 
            else if (level == 2 && (inputChar >= 'a' && inputChar <= 'z')) { isValidChar = true; } 
            else if (level == 3 && ((inputChar >= '0' && inputChar <= '9') || (inputChar >= 'a' && inputChar <= 'z'))) { isValidChar = true; }
            
            // Chỉ thêm ký tự nếu hợp lệ và chưa đủ độ dài
            if (isValidChar && currentInput.length() < maxKeyLength) {
                currentInput += inputChar;
                updateInputDisplay(currentPlayer);
            }
        }
    }
    
    // Xử lý nút ĐOÁN
    guessButton.hovered = guessButton.contains(mousePos.x, mousePos.y);

    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
        if (guessButton.contains(mousePos.x, mousePos.y) && currentInput.length() == maxKeyLength) {
            processGuess(currentPlayer);
        }
        // Xử lý click vào các nút ký tự (A B C D...)
        // ...
    }
    
    return GAME_PVP;
}

// KHÔNG SỬA ĐỔI: Logic update của bạn được giữ nguyên
void GamePVP::update(float dt) {
    if (!isGameOver) {
        guessButton.update(dt);
    }
}

// KHÔNG SỬA ĐỔI: Logic draw của bạn được giữ nguyên
void GamePVP::draw(sf::RenderWindow& win) {
    drawHeader(win, L"TRẬN CHIẾN ĐOÁN KEY", 80);
    
    for (int i = 0; i < maxKeyLength; ++i) {
        sf::RectangleShape* currentInputBoxes = (currentPlayer == 1) ? inputBoxes1 : inputBoxes2;
        
        if (inputKeyStatus[i] == 1) {
            currentInputBoxes[i].setFillColor(sf::Color(124, 252, 0)); // Màu xanh lá chuối (Lawn Green)
        } else {
            currentInputBoxes[i].setFillColor(sf::Color(50, 50, 80)); 
        }
    }
    
    drawPlayerArea(win, 1);
    drawPlayerArea(win, 2);
    
    guessButton.draw(win, scaleX, scaleY);
    
    if (isGameOver) {
        // ... (Vẽ màn hình kết thúc game) ...
    }
}

// HOÀN THIỆN: Logic drawPlayerArea để vẽ tất cả các thành phần GUI
void GamePVP::drawPlayerArea(sf::RenderWindow& win, int playerID) {
    
    // 1. Vẽ ô nhập liệu hiện tại (HAND)
    sf::RectangleShape* inputBoxes = (playerID == 1) ? inputBoxes1 : inputBoxes2;
    sf::Text* inputTexts = (playerID == 1) ? inputTexts1 : inputTexts2;

    for (int i = 0; i < maxKeyLength; ++i) {
        win.draw(inputBoxes[i]);
        win.draw(inputTexts[i]);
    }
    
    // 2. Vẽ các nút ký tự (A B C D...)
    sf::RectangleShape* keyButtons = (playerID == 1) ? keyButtons1 : keyButtons2;
    sf::Text* keyButtonTexts = (playerID == 1) ? keyButtonTexts1 : keyButtonTexts2;

    for (int i = 0; i < maxKeyLength; ++i) { 
        win.draw(keyButtons[i]);
        win.draw(keyButtonTexts[i]);
    }

    // 3. Vẽ lịch sử đoán và kết quả (guessGrid, resultLights)
    const std::vector<GuessRecord>& currentGuesses = (playerID == 1) ? user1Guesses : user2Guesses;
    sf::RectangleShape (*guessGrid)[8] = (playerID == 1) ? guessGrid1 : guessGrid2;
    sf::RectangleShape (*resultLights)[2] = (playerID == 1) ? resultLights1 : resultLights2;

    for (size_t r = 0; r < currentGuesses.size(); ++r) {
        const GuessRecord& record = currentGuesses[r];
        
        int correctPosCount = 0;
        int correctNumCount = 0;

        for (int c = 0; c < maxKeyLength; ++c) {
            
            sf::Color boxColor = sf::Color(30, 30, 30);
            // matchStatus[c]: 1=Đúng vị trí (Green), 2=Đúng số/Sai vị trí (Yellow)
            if (record.matchStatus[c] == 1) {
                boxColor = sf::Color::Green; 
                correctPosCount++;
            } else if (record.matchStatus[c] == 2) {
                boxColor = sf::Color::Yellow; 
                correctNumCount++;
            }
            
            guessGrid[r][c].setFillColor(boxColor);
            win.draw(guessGrid[r][c]);
            
            // Vẽ ký tự đoán lên ô
            sf::Text guessChar;
            guessChar.setFont(font);
            guessChar.setCharacterSize(20 * scaleY);
            guessChar.setFillColor(sf::Color::White);
            guessChar.setString(record.guess.substr(c, 1));
            
            centerText(guessChar);
            guessChar.setPosition(
                guessGrid[r][c].getPosition().x + guessGrid[r][c].getSize().x / 2.0f,
                guessGrid[r][c].getPosition().y + guessGrid[r][c].getSize().y / 2.0f - 2
            );
            win.draw(guessChar);
        }

        // Vẽ đèn kết quả (Result Lights)
        // Đèn 1 (Đúng vị trí) - Giả định màu Đỏ là báo hiệu kết quả
        resultLights[r][0].setFillColor((correctPosCount > 0) ? sf::Color::Red : sf::Color::Black);
        win.draw(resultLights[r][0]);

        // Đèn 2 (Đúng số, sai vị trí) - Giả định màu Trắng là báo hiệu kết quả
        resultLights[r][1].setFillColor((correctNumCount > 0) ? sf::Color::White : sf::Color::Black);
        win.draw(resultLights[r][1]);
    }

    // 4. Vẽ Trái tim (Hearts) và Bóng đèn gợi ý (Hint Lights)
    sf::RectangleShape* currentHearts = (playerID == 1) ? hearts1 : hearts2;
    sf::CircleShape* currentHintLights = (playerID == 1) ? hintLights1 : hintLights2;

    // Vẽ Trái tim (Giữ nguyên logic vẽ mặc định)
    for (int i = 0; i < 5; ++i) { 
        win.draw(currentHearts[i]); 
    }
    // Vẽ Bóng đèn gợi ý (Giữ nguyên logic vẽ mặc định)
    win.draw(currentHintLights[0]);
    win.draw(currentHintLights[1]);
}