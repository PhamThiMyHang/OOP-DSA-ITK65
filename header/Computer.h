#ifndef COMPUTER_H
#define COMPUTER_H

#include "User.h"
#include<iostream>
#include <string>
using namespace std;

class Computer: public User{
private:
public:
    Computer();
    Computer(string name, string keyDo, string keyDoan, int maxLenght, int IDLevel);
    Computer(Computer &a);
    //void nhapTen();
    void taoKeyNgauNhien(int length = 5);
  //  string getKey() const;
    void nhapKeyDoan();
    //Them hàm tạo name gán nhãn cho computer 
};

#endif
