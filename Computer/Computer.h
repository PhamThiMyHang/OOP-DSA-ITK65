#include<iostream>
#include <string>
using namespace std;

class Computer {
private:
    string ten;
    string key;   // key mà máy tạo hoặc máy đoán
public:
    Computer();
    void nhapTen();
    void taoKeyNgauNhien(int length = 5);
    string getKey() const;
    void doanKey(const string& keyToGuess);
};


