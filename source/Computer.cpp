#include "../header/Computer.h"
#include <cstdlib>
#include <ctime>

Computer::Computer(): User() {

}
Computer::Computer(string name, string keyDo, string keyDoan, int maxLenght, int IDLevel): User(name, keyDo, keyDoan, maxLenght,IDLevel){

}
Computer::Computer(Computer &a): User(a){

}

void Computer::taoKeyNgauNhien(int length) {
    srand((unsigned)time(nullptr));
    string key;
    for (int i = 0; i < length; ++i) {
        char c = 'A' + rand() % 26;
        key += c;
    }
    string ten;
    ten =this->getName();
    this->setKeyDo(key);
    cout << ten << " da tao key ngau nhien.\n";
}

void Computer::nhapKeyDoan() {
    // đơn giản: máy đoán một lần ngẫu nhiên (ở đây không tối ưu)
    srand((unsigned)time(nullptr));
    string guess = "";
    int len = this->getMaxLenght();
    for (int i = 0; i < len; ++i) {
        char c = 'A' + rand() % 26;
        guess += c;
    }
    string ten = this->getName();
    cout << ten << " doan key: " << guess << endl;
    this->GhiKeyDoanFile(ten, guess);
}
