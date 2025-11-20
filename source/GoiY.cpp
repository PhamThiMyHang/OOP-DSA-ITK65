
#include <iostream>
#include <string>
#include "GoiY.h"
using namespace std;


GoiY::GoiY(){
	this->luotGY = 0;
	luotGYDaDung = 0;
}
GoiY::GoiY(int luotGYConLai, int luotGYDaDung){
	this->luotGY = luotGY;
	this->luotGYDaDung = luotGYDaDung;
}
GoiY::GoiY(GoiY &a){
	this->luotGY = a.luotGY;
	this->luotGYDaDung =a.luotGYDaDung;
	
}
void GoiY::setLuotGoiY(int luotGY){
	this->luotGY = luotGY;
}
int GoiY::getLuotGoiY(){
	return this->luotGY;
}
void GoiY::setLuotGoiYDaDung(int luotGYDaDung){
	this->luotGYDaDung = luotGYDaDung;
}
int GoiY::getLuotGoiYDaDung(){
	return this->luotGYDaDung;
}
char GoiY::kyTuGoiY(string KeyDo){
	return KeyDo[this->luotGYDaDung];
}
void GoiY::hienThiKyTuGoiY(string KeyDo){
	//Sua cho no vao GUI
	cout<<this->kyTuGoiY(KeyDo);
	this->luotGYDaDung ++;
}
bool GoiY::CheckDieuKienGoiY(){
	if(this->luotGYDaDung == this->luotGY){
		return 0;
	}else{
		return 1;
	}
}
void GoiY::dungGoiY(string KeyDo){
	if(this->CheckDieuKienGoiY() == 1){
		this->hienThiKyTuGoiY(KeyDo);
	}else{
		cout<<"Het Luot"<<endl;
		return;
	}
}

