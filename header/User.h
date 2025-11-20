#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "GoiY.h"
using namespace std;
class User{
	private:
		string name, keyDo, keyDoan;
		int maxLenght;
		int IDLevel; 
		GoiY GY;
	public:
		User();
		User(string name, string keyDo, string keyDoan, int maxLenght,int IDLevel );
		User(User &a);
		~User();
		virtual void nhapKeyDo();
		virtual void nhapKeyDoan();
		string getKeyDoan();
		string getKeyDo();
		void setKeyDoan(string keyDoan);
		void setKeyDo(string keyDo);
		void setMaxLenght(int maxLenght);
        int getMaxLenght();
		void GhiKeyDoanFile(string ttep, string keyDoan);
		void DocKeyDoanFile(string ttep,int &cout, string *keyDoan);
        string getName();
        void setName(const string name);
        int GetIDLevel();
		void SetIDLevel(int IDLevel);
		void GetGoiY(string KeyCanDoan);
};

#endif