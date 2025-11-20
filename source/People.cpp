#include "../header/People.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

People::People(): User() {
}
People::People(string name, string keyDo, string keyDoan, int maxLenght, int IDLevel): User(name, keyDo, keyDoan, maxLenght, IDLevel){

}
People::People(People &a): User(a){

}

/*
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
*/
void People::nhapKeyDo() {
    string key;
    string ten ;
    ten = this->getName();
    do{
    //    cout << ten << " nhap key bi mat: ";
        cin>>key;
    }while (key.length() != this->getMaxLenght() );
    this->setKeyDo(key);
}

void People::luuKey() {
    cout << "Key da duoc luu.\n";
}

void People::nhapKeyDoan() {
    string guess;
    string ten ;
    ten = this->getName();
    do{
        cin>>guess;
    }while(guess.length() != this->getMaxLenght());
    this->setKeyDoan(guess);
    this->GhiKeyDoanFile(ten,guess);
   /* int n = this->getMaxLenght();
    for(int i=0; i < n; i++){
        
    }*/
}

