#ifndef NGUOIQUANTRO_H
#define NGUOIQUANTRO_H

#include "People.h"
#include "Computer.h"
#include "Level.h"
#include "GoiY.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class NguoiQuanTro {
  private:
  //MyHang:  đổi kiểu people thàng mảng
      People a[2];              // Hai người chơi (người - người hoặc người - máy)
      Computer c;               // Máy tính (nếu chơi với máy)
      Level L;                  // Level hiện tại
      int maxLength;            // Độ dài key
      int mode;                 // 1: Người vs Máy | 2: Người vs Người

    int Winner; // 1 là User1 thắng , 2 là User hoặc Computer thắng 

  public:
      NguoiQuanTro();

      void firstUser();            // Tạo người chơi 1
      void secondUser();           // Chọn chơi với người hoặc máy
      void chonLevel(int lv);            // Chọn cấp độ chơi
      int getMaxLength();          // Lấy độ dài key
      void hamTaoCacNguoiChoi();  // Tạo người chơi và key
      void hamTaoKey();           //Mỹ Hằng: Them hào tạo key
      void play();                 // Vòng chơi chính
      void ketThucVan();            // Kết thúc ván
      void showHint(string guess); // Gợi ý tùy theo level
      void showHistory();          // Xem lại các lần đoán trong khi chơi
      int resetGame();            // Chơi lại
      void Game();
      int getWinner();
      void setWinner(int n);
      int getMode();
      void setMode(int mode);
      string KeyNhap(int i, string key);
      void KeyDoNhap(int i, string keynhap);
      void KeyDoanNhap(int i, string keynhap);
      string KeyDo(int i);
      string KeyDoComputer();
      string KeyDoanComputer();
      int checkKey(int i, int mode, int *b);
      void generateKeyForComputer();
      void setIDlevel(int lv);
      int getIDlevel();
};

#endif // NGUOIQUANTRO_H
