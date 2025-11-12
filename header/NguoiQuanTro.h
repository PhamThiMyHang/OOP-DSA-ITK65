#ifndef NGUOIQUANTRO_H
#define NGUOIQUANTRO_H

#include "People.h"
#include "Computer.h"
#include "Level.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class NguoiQuanTro {
private:
    People a[2];              // Hai người chơi (người - người hoặc người - máy)
    Computer c;               // Máy tính (nếu chơi với máy)
    Level L;                  // Level hiện tại
    int maxLength;            // Độ dài key
    vector<string> history;   // Lưu lịch sử đoán (chỉ hiển thị trong khi chơi)
    int mode;                 // 1: Người vs Máy | 2: Người vs Người
    int diemNguoi1;           // Điểm người 1
    int diemNguoi2;           // Điểm người 2
    string keyBiMat;          // Key bí mật cần đoán

public:
    NguoiQuanTro();

    void firstUser();            // Tạo người chơi 1
    void secondUser();           // Chọn chơi với người hoặc máy
    void chonLevel();            // Chọn cấp độ chơi
    int getMaxLength();          // Lấy độ dài key
    void hamTaoCacNguoiChoi();  // Tạo người chơi và key
    void play();                 // Vòng chơi chính
    int ketThucVan();            // Kết thúc ván
    void showHint(string guess); // Gợi ý tùy theo level
    void showHistory();          // Xem lại các lần đoán trong khi chơi
    void resetGame();            // Chơi lại
};

#endif // NGUOIQUANTRO_H
