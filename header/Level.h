#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

class Level {
private:
    string keyPlayer;            // Key người chơi (nếu có)
    string keySecret;            // Key bí mật
    int levelId;                 // Cấp độ: 1 - dễ, 2 - trung bình, 3 - khó
    int maxLength;               // Độ dài key (4–6 ký tự)
    int maxHint;                 // Số lượt gợi ý tối đa
    int hintUsed;                // Đã dùng bao nhiêu gợi ý
    int hintIndex;               // Gợi ý kế tiếp
    vector<string> history;      // Lịch sử đoán trong ván chơi

    // Hàm phụ trợ
    string makeCharset() const;
    string generateRandomKey(int len);

public:
    // --- Khởi tạo ---
    Level();
    Level(int id, int len);

    // --- Thiết lập và lấy thông tin level ---
    void setLevelId(int id);
    int getLevelId() const;
    void chooseLevel();          // Chọn cấp độ tương tác (nếu cần)
    int getLevel() const;        // Lấy giá trị cấp độ hiện tại
    int getMaxLength() const;    // Lấy độ dài tối đa key

    // --- Tạo level mới ---
    void createLevel(int id, int len);

    // --- Quản lý key ---
    void setKeyPlayer(const string& key);
    void setKeySecret(const string& key);
    string getKeyPlayer() const;
    string getKeySecret() const;

    // --- Kiểm tra đoán ---
    int checkKey(const string& guess);  
    pair<int, int> checkGuess(const string& guess);

    // --- Gợi ý ---
    string giveHint();

    // --- Lịch sử ---
    void addHistory(const string& guess);
    const vector<string>& getHistory() const;

    // --- Hiển thị thông tin ---
    void showInfo() const;

    // --- Hỗ trợ ---
    bool isCorrect(const string& guess) const;
    void resetHints();
};

#endif
