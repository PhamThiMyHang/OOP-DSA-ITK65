#include "../header/User.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

User::User(){
	this->maxLenght = 0;
	this->name ="";
	this->keyDo = "";
	this->keyDoan = "";
	this->IDLevel = 1;
}
User::User(string name, string keyDo, string keyDoan, int maxLenght, int IDLevel){
	this->name = name;
	this->keyDoan = keyDoan;
	this->keyDo = keyDo;
	this->maxLenght = maxLenght;
	this->IDLevel =  IDLevel;
}
User::User(User &a){
	this->name = a.name;
	this->keyDo = a.keyDo;
	this->keyDoan = a.keyDoan;
	this->maxLenght =a.maxLenght;
	this->IDLevel = a.IDLevel;
}
User::~User(){
	
}	
string User::getName(){
	return this->name;
}
void User:: setName(const string name){
	this->name = name;
}
// 2 hàm ảo
void User::nhapKeyDo(){
	cout<<"nhap key do: ";
	cin>>this->keyDo;
}
void User::nhapKeyDoan(){
	cout<<"nhap key doan: ";
	cin>>this->keyDoan;
}
//
string User::getKeyDo(){
	return this->keyDo;
}
string User::getKeyDoan(){
	return this->keyDoan;
}
void User:: setMaxLenght(int maxLenght){
	this->maxLenght = maxLenght;
}
int User:: getMaxLenght(){
	return this->maxLenght;
}
void User::setKeyDo(string keyDo){
	this->keyDo = keyDo;
}
void User::setKeyDoan(string keyDoan){
	this->keyDoan = keyDoan;
}
int User::GetIDLevel(){
    return this->IDLevel;
}

void User::SetIDLevel(int IDLevel){
    this->IDLevel = IDLevel;
}

void User::GetGoiY(string KeyCanDoan){
	GY.dungGoiY(KeyCanDoan);
}

void User::GhiKeyDoanFile(string ttep, string keyDoan){
	ofstream file(ttep.c_str(), ios::app); 
    if (!file) {
        cout << "Khong mo duoc file!" << endl;
        return ;
    }else{
    file<<keyDoan<<endl;	
	}
    file.close();
    return ;
}
void User::DocKeyDoanFile(string ttep,int &count, string *keyDoan){
	ifstream file (ttep.c_str());
	if (!file) {
        cout << "Khong mo duoc file!" << endl;
        return ;
    }else{
    	count = 0;
    	  string temp;
    	while (getline(file, temp)) {
        count++;
        keyDoan = new string[count];
        file.clear();
    	file.seekg(0, ios::beg);
    	for (int i = 0; i < count; ++i) {
        	getline(file, keyDoan[i]);
        }
    }
    file.close();
    }
}
/*
int main(){
	User a;
	a.nhapKeyDo();
	a.nhapKeyDoan();
	string KeyDoan = a.getKeyDoan();
	cout<<KeyDoan<<endl;
	a.GhiKeyDoanFile("User1.txt",KeyDoan);
	a.setKeyDoan("Pham Thi My Hang");
	KeyDoan = a.getKeyDoan();
	a.GhiKeyDoanFile("User1.txt",KeyDoan);
	string * ListKey;
	int count=0;
	a.DocKeyDoanFile("User1.txt",count, ListKey);
	for(int i=0; i< count; i++){
		cout<<ListKey[i]<<endl;
	}
	
}
*/