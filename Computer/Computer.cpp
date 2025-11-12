#include "Computer.h"
#include <cstdlib>
#include <ctime>

Computer::Computer() {
    ten = "MayTinh";
    key = "";
}

void Computer::nhapTen() {
    cout << "Nhap ten may tinh (hoac de mac dinh " << ten << "): ";
    string temp;
    getline(cin, temp);
    if (!temp.empty()) ten = temp;
}

void Computer::taoKeyNgauNhien(int length) {
    srand((unsigned)time(nullptr));
    key = "";
    for (int i = 0; i < length; ++i) {
        char c = 'A' + rand() % 26;
        key += c;
    }
    cout << ten << " da tao key ngau nhien.\n";
}

string Computer::getKey() const {
    return key;
}

void Computer::doanKey(const string& keyToGuess) {
    // đơn giản: máy đoán một lần ngẫu nhiên (ở đây không tối ưu)
    srand((unsigned)time(nullptr));
    string guess = "";
    int len = keyToGuess.length();
    for (int i = 0; i < len; ++i) {
        char c = 'A' + rand() % 26;
        guess += c;
    }
    cout << ten << " doan key: " << guess << endl;
    if (guess == keyToGuess) {
        cout << "May tinh doan dung!\n";
    } else {
        cout << "May tinh doan sai! KEY dung la: " << keyToGuess << endl;
    }
}
