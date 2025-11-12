#include "People.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

People::People() {
    ID = "";
    ten = "";
    key = "";
}

void People::nhapTen() {
    cout << "Nhap ten nguoi choi: ";
    getline(cin, ten);
}

void People::taoID() {
    cout << ten << ", ban muon:\n";
    cout << "1. Tu nhap ID\n";
    cout << "2. He thong tao ID ngau nhien\n";
    cout << "Lua chon (1/2): ";
    string choice;
    getline(cin, choice);

    if (choice == "1") {
        cout << "Nhap ID cua ban: ";
        getline(cin, ID);
    } else {
        srand((unsigned)time(nullptr));
        ID = "";
        for (int i = 0; i < 6; ++i) {
            char c = 'A' + rand() % 26;
            ID += c;
        }
        cout << "ID ngau nhien da duoc tao: " << ID << endl;
    }
}

void People::taoKey() {
    cout << ten << ", nhap key bi mat: ";
    getline(cin, key);
}

void People::luuKey() {
    cout << "Key da duoc luu.\n";
}

void People::nhapTenDoan() {
    cout << "Nguoi choi doan, nhap ten: ";
    getline(cin, ten);
}

bool People::doanKey(const string& keyToGuess) {
    cout << ten << ", doan key: ";
    string guess;
    getline(cin, guess);
    if (guess == keyToGuess) {
        cout << "Chinh xac! Ban da doan dung KEY!\n";
        return true;
    } else {
        cout << "Sai roi! KEY dung la: " << keyToGuess << endl;
        return false;
    }
}

string People::getKey() const {
    return key;
}
