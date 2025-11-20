#ifndef PEOPLE_H
#define PEOPLE_H
#include "User.h"
#include <string>
#include <iostream>
#include <GoiY.h>
using namespace std;

class People: public User {
private: 
public:
    People();
    People(string name, string keyDo, string keyDoan, int maxLenght, int IDLevel);
    People(People &a);
  //  void nhapTen();
 //   void taoID();
 //Sửa tên hàm 
    void nhapKeyDo();
    void luuKey();
    // chế độ đoán
    void nhapKeyDoan();
  //  bool doanKey(const string& keyToGuess);
    // lấy key để người khác đoán
  //  string getKey() const;
};

#endif
