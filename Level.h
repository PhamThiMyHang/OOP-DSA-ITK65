#ifndef LEVEL_H
#define LEVEL_H

#include <string>
using namespace std;

class Level {
private:
    string Key1;        // Từ khóa 1
    string Key2;        // Từ khóa 2
    int IDLevel;        // Mã cấp độ
    int MaxLength;      // Độ dài chuỗi
    bool IncludeLetters; // thêm: true nếu có cả chữ cái (level 3)

public:
    Level();            // Constructor mặc định
    Level(int l);       // Constructor có tham số

    void SetIDLevel(int id);
    void SetKey1(string key);
    void SetKey2(string key);

    string GetKey1();
    string GetKey2();
    int GetIDLevel();
    // hàm thêm: 
    int GetMaxLength();
    //hàm thêm: 
    bool HasLetters();

    void CreateLevel(int l);

    // Hàm thêm: kiểm tra chuỗi nhập có hợp lệ theo cấp độ
    bool IsValidInput(string input);

    // Hàm thêm: xử lý đoán chuỗi theo cấp độ
    void CheckKeyDoan(string keyDoan, string keyDung);
};

#endif