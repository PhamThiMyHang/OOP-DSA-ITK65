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

int Level::GetIDLevel() {
    return IDLevel;
}

void Level::SetMaxLength(int MaxLength){
    this->MaxLength = MaxLength;
}

int Level::GetMaxLength() {
    return MaxLength;
}

bool Level::GetIncludeLetters(){
    return this->IncludeLetters;
}

void Level::SetIncludeLetters(bool IncludeLetters){
    this->IncludeLetters = IncludeLetters;
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

int Level::CheckKeyDoan(string keyDoan, string keyDung, int *a) {
    cout<<keyDoan<<endl;
    cout<<keyDung<<endl;
    if(keyDoan.length() != keyDung.length()) return 0;
    int  count= 0;
    int length= keyDoan.length() ;
    for (int i = 0; i < length; i++) {
        if (keyDoan[i] == keyDung[i]) {
            cout<<i<<keyDoan[i]<<"vs"<<keyDung[i]<<endl;
            a[i] = 1;
            count = count +1;
        }
    }
   return count;
}

void Level::ketQua(string keyDoan, string keyDung, int &mode){
    mode =0;
    int *a = new int [this->MaxLength];
    for(int i=0; i< this->MaxLength;i++){
        a[i]=0;
    }
    int check =this->CheckKeyDoan(keyDoan, keyDung, a);
    if(check!=0 && check !=this->MaxLength){
        cout << "Có " << check  << " vị trí đúng.\n";
        int i=0;
        for(int i=0; i< this->MaxLength;i++){
            if(a[i]!= 0){
                cout<< i<<" ";
            }
        }
        cout<<"\n ";
    }else if( check==0 ){
        cout<<" khong co ky tu doan dung"<<endl;
    }else{
        mode=1;
    }
}
