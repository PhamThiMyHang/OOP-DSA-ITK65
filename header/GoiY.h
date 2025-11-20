#ifndef GOIY_H
#define GOIY_H
#include <iostream>
#include <string>

using namespace std;

class GoiY{
	private:
		int luotGY;
		int luotGYDaDung;
	public:
		GoiY();                  // ba hamf tao
		GoiY(int luotGY, int luotGYDaDung);
		GoiY(GoiY &a);
		void setLuotGoiY(int luotGY);        //Tuan theo nguyen tac co j set, get cai do
		int getLuotGoiY();
		void setLuotGoiYDaDung(int luotGY);
		int getLuotGoiYDaDung();
		char kyTuGoiY(string KeyDo);              // 2 ham nay von gop chung lai duoc nhung ma dung GUI nen tach ra cho de dung
		void hienThiKyTuGoiY(string KeyDo);
		bool CheckDieuKienGoiY();
		void dungGoiY(string KeyDo);
};
#endif