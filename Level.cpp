#include "Level.h"
#include <iostream>
#include <cctype>
using namespace std;

Level::Level() {
    CreateLevel(1);
}

Level::Level(int l) {
    CreateLevel(l);
}

void Level::SetIDLevel(int id) {
    IDLevel = id;
}

void Level::SetKey1(string key) {
    Key1 = key;
}

void Level::SetKey2(string key) {
    Key2 = key;
}

string Level::GetKey1() {
    return Key1;
}

string Level::GetKey2() {
    return Key2;
}

int Level::GetIDLevel() {
    return IDLevel;
}

int Level::GetMaxLength() {
    return MaxLength;
}

bool Level::HasLetters() {
    return IncludeLetters;
}

void Level::CreateLevel(int l) {
    IDLevel = l;

    switch (l) {
        case 1:
            MaxLength = 4;
            IncludeLetters = false;
            break;
        case 2:
            MaxLength = 5;
            IncludeLetters = false;
            break;
        case 3:
            MaxLength = 6;
            IncludeLetters = true;
            break;
        default:
            MaxLength = 4;
            IncludeLetters = false;
    }

    Key1 = "";
    Key2 = "";
}


bool Level::IsValidInput(string input) {
    if (input.length() != MaxLength) {
        cout << "Chuỗi phải có đúng " << MaxLength << " ký tự.\n";
        return false;
    }

    bool hasDigit = false, hasAlpha = false;

    for (char c : input){// này là c sẽ duyệt từng ký tự trong input 
        if (isdigit(c)) hasDigit = true;//isdigi: dùng để kiểm tra ký tự có phải là số, nằm trong thư viện <cctype>
        if (isalpha(c)) hasAlpha = true;//isalpha: dùng để kiểm tra ký tự có phải là chữ, nằm trong thư viện <cctype>

        if (!IncludeLetters && !isdigit(c)) {
            cout << "Chỉ được nhập số! Vui lòng nhập lại.\n";
            return false;
        }
    }

    if (IncludeLetters && !(hasDigit && hasAlpha)) {
        cout << "Phải nhập cả số và chữ! Vui lòng nhập lại.\n";
        return false;
    }

    return true;
}

void Level::CheckKeyDoan(string keyDoan, string keyDung) {
    int length = min(keyDoan.size(), keyDung.size());
    int count = 0;

    if (IDLevel == 1) {
        cout << "Kết quả đoán: ";
        for (int i = 0; i < length; ++i) {
            if (keyDoan[i] == keyDung[i]) {
                cout << keyDoan[i];
            } else {
                cout << "_";
            }
        }
        cout << "\n";
    } else {
        for (int i = 0; i < length; ++i) {
            if (keyDoan[i] == keyDung[i]) ++count;
        }
        cout << "Có " << count << " vị trí đúng.\n";
    }
}