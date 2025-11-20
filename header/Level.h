#ifndef LEVEL_H
#define LEVEL_H

#include <string>
using namespace std;

class Level {
    private:
        int IDLevel;        // Mã cấp độ
        int MaxLength;      // Độ dài chuỗi
        bool IncludeLetters; // thêm: true nếu có cả chữ cái (level 3)

    public:
        Level();            // Constructor mặc định
        Level(int l);       // Constructor có tham số

        void SetIDLevel(int id);
        int GetIDLevel();
        // hàm thêm: 
        int GetMaxLength();
        void SetMaxLength(int MaxLengh);

        void  SetIncludeLetters(bool IncludeLetters);
        bool GetIncludeLetters();

        //hàm thêm:
        void CreateLevel(int l);

        // Hàm thêm: kiểm tra chuỗi nhập có hợp lệ theo cấp độ
        bool IsValidInput(string input);

        // Hàm thêm: xử lý đoán chuỗi theo cấp độ
        int CheckKeyDoan(string keyDoan, string keyDung, int *a);
        void ketQua(string keyDoan, string keyDung, int &mode);
};

#endif