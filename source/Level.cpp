#include"../header/Level.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ==========================
// ===== Hàm phụ trợ ========
// ==========================

string Level::makeCharset() const {
    switch (levelId) {
        case 1: return "0123456789";  // Dễ
        case 2: return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Trung bình
        case 3: return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Khó
        default: return "0123456789";
    }
}

string Level::generateRandomKey(int len) {
    string charset = makeCharset();
    string result = "";
    srand((unsigned)time(nullptr));
    for (int i = 0; i < len; i++) {
        result += charset[rand() % charset.size()];
    }
    return result;
}

// ==========================
// ===== Hàm khởi tạo =======
// ==========================

Level::Level() {
    levelId = 1;
    maxLength = 4;
    maxHint = 4;
    hintUsed = 0;
    hintIndex = 0;
    keyPlayer = keySecret = "";
}

Level::Level(int id, int len) {
    createLevel(id, len);
}

// ==========================
// ===== Thiết lập Level ====
// ==========================

void Level::setLevelId(int id) {
    levelId = id;
}

int Level::getLevelId() const {
    return levelId;
}

void Level::chooseLevel() {
    cout << "\n=== Chon do kho ===\n";
    cout << "1. De (so tu 0-9)\n";
    cout << "2. Trung binh (chu in hoa va so)\n";
    cout << "3. Kho (chu thuong, chu hoa va so)\n";
    cout << "Nhap lua chon: ";
    cin >> levelId;

    if (levelId < 1 || levelId > 3) {
        cout << "Lua chon khong hop le! Mac dinh la De.\n";
        levelId = 1;
    }

    if (levelId == 1) maxLength = 4;
    else if (levelId == 2) maxLength = 5;
    else maxLength = 6;

    maxHint = maxLength / 2;
    hintUsed = 0;
    hintIndex = 0;
    keyPlayer = keySecret = "";
    history.clear();
}

int Level::getLevel() const {
    return levelId;
}

int Level::getMaxLength() const {
    return maxLength;
}

// ==========================
// ===== Tạo Level mới ======
// ==========================

void Level::createLevel(int id, int len) {
    levelId = id;
    maxLength = len;
    maxHint = len / 2;
    hintUsed = 0;
    hintIndex = 0;
    keyPlayer = keySecret = generateRandomKey(len);
    history.clear();
}

// ==========================
// ===== Quản lý Key =========
// ==========================

void Level::setKeyPlayer(const string& key) {
    keyPlayer = key;
}

void Level::setKeySecret(const string& key) {
    keySecret = key;
}

string Level::getKeyPlayer() const {
    return keyPlayer;
}

string Level::getKeySecret() const {
    return keySecret;
}

// ==========================
// ===== Kiểm tra đoán =======
// ==========================

int Level::checkKey(const string& guess) {
    return (guess == keySecret) ? 1 : 0;
}

pair<int, int> Level::checkGuess(const string& guess) {
    int bulls = 0, cows = 0;
    for (size_t i = 0; i < guess.size() && i < keySecret.size(); ++i) {
        if (guess[i] == keySecret[i]) bulls++;
        else if (keySecret.find(guess[i]) != string::npos) cows++;
    }
    return {bulls, cows};
}

// ==========================
// ===== Gợi ý ==============
// ==========================

string Level::giveHint() {
    if (hintUsed >= maxHint || hintIndex >= (int)keySecret.size())
        return "Het goi y!";
    string hint = "Ky tu thu " + to_string(hintIndex + 1) +
                  " la: " + string(1, keySecret[hintIndex]);
    hintUsed++;
    hintIndex++;
    return hint;
}

// ==========================
// ===== Lịch sử ============
// ==========================

void Level::addHistory(const string& guess) {
    history.push_back(guess);
}

const vector<string>& Level::getHistory() const {
    return history;
}

// ==========================
// ===== Thông tin =========
// ==========================

void Level::showInfo() const {
    cout << "Cap do: " << levelId
         << " | Do dai toi da: " << maxLength
         << " | Goi y da dung: " << hintUsed << "/" << maxHint << endl;
}

// ==========================
// ===== Hỗ trợ =============
// ==========================

bool Level::isCorrect(const string& guess) const {
    return guess == keySecret;
}

void Level::resetHints() {
    hintUsed = 0;
    hintIndex = 0;
}
