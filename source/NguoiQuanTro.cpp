#include "../header/NguoiQuanTro.h"
#include <cstdlib>
#include <ctime>
#include <vector>


NguoiQuanTro::NguoiQuanTro() {
 //   diemNguoi1 = diemNguoi2 = 0;
    mode = 1;
    maxLength =  4;
    Winner = 0;
    srand((unsigned)time(nullptr));
    
}
  int NguoiQuanTro::getWinner(){
    return this->Winner;
  }
      void NguoiQuanTro::setWinner(int n){
        this->Winner = n;
      }
      int NguoiQuanTro::getMode(){
        return this->mode;
      }
      void NguoiQuanTro::setMode(int mode){
        this->mode =mode;
      }
// ======================= NGƯỜI CHƠI ==========================
void NguoiQuanTro::firstUser() {
    cout << "\n=== TAO NGUOI CHOI 1 ===\n";
        a[0].setName("User1");
}

void NguoiQuanTro::secondUser() {

    if (mode == 2) {
        cout << "\n=== TAO NGUOI CHOI 2 ===\n";
        a[1].setName("User2");
    } else {
        cout << "\n=== CHOI VOI MAY ===\n";
        c.setName("Computer");
    }
}

// ======================= CHỌN LEVEL ==========================
void NguoiQuanTro::chonLevel(int lv) {
    
    if (lv < 1 || lv > 3) lv = 1;
        L.CreateLevel(lv);
    maxLength = L.GetMaxLength();
    a[0].setMaxLenght(maxLength);
    if(mode == 2)
         a[1].setMaxLenght(maxLength);
    else
         c.setMaxLenght(maxLength);
}



// My Hang bổ sung và sửa function hamTaoCacNguoiChoi

void NguoiQuanTro::hamTaoCacNguoiChoi(){
  //  cout << "\nBan muon choi voi may hay nguoi khac?\n";
  //  cout << "0. May tinh\n   1. Nguoi \nChon: ";
    //cin >> mode;
    //cin.ignore();
    this->firstUser();
    this->secondUser();
}
 void NguoiQuanTro::generateKeyForComputer(){
    c.taoKeyNgauNhien();
 }

//Nghiên cứu lại cách làm sao nhập ký tự vào trong chức năng tạo Key
// ======================= TẠO KEY ==========================
void NguoiQuanTro::hamTaoKey() {
    cout << "\n=== TAO KEY ===\n";
    if (mode == 1) { // Người vs Máy
        c.taoKeyNgauNhien(maxLength);
        a[0].nhapKeyDo();
    } else { // Người vs Người
        a[0].nhapKeyDo();
        a[1].nhapKeyDo();
     //   system("cls"); // ẩn key để người 1 không thấy 
        //Thay bằng GUI
    }
    cout << "Key bi mat da duoc tao. Bat dau doan!\n";
}



/*
// ======================= GỢI Ý ==========================
void NguoiQuanTro::showHint(string guess) {
    int correct = L.checkKey(guess); // kiểm tra theo cấp độ
    if (L.getLevelId() == 1) {
        // Level dễ: hiển thị vị trí đúng
        cout << "Goi y (vi tri dung): ";
        for (int i = 0; i < guess.size(); ++i) {
            if (guess[i] == keyBiMat[i]) cout << guess[i];
            else cout << "_";
        }
        cout << endl;
    } else if (L.getLevelId() == 2) {
        // Level TB: chỉ thông báo số ký tự đúng
        cout << "Ban doan dung " << correct << " so!\n";
    } else {
        // Level khó: chỉ thông báo số ký tự đúng (chữ + số)
        cout << "Ban doan dung " << correct << " ky tu!\n";
    }
}
*/



// ======================= LỊCH SỬ ==========================
void NguoiQuanTro::showHistory() {
    string *history1;
    int n1 = 0;
    string *history2;
    int n2 = 0;
    if(mode == 1){
        a[0].DocKeyDoanFile("User1", n1, history1);
        c.DocKeyDoanFile("Computer", n2, history2);
    }else{
        a[0].DocKeyDoanFile("User1", n1, history1);
        a[1].DocKeyDoanFile("User2", n2, history2);
    }
    cout<<"List 1:"<<endl;
    for(int i=0;i<n1;i++){
        cout<<history1[i]<<endl;
    }
    cout<<"List 2:"<<endl;
    for(int i=0;i<n2;i++){
        cout<<history2[i]<<endl;
    }

}
void NguoiQuanTro::setIDlevel(int lv){
    L.SetIDLevel(lv);
}
int NguoiQuanTro:: getIDlevel(){
return L.GetIDLevel();
}
void NguoiQuanTro::KeyDoNhap(int i, string keynhap){
     a[i].setKeyDo(keynhap);
}
void NguoiQuanTro::KeyDoanNhap(int i, string keynhap){
     a[i].setKeyDoan(keynhap);
     a[i].GhiKeyDoanFile(a[i].getName(), keynhap );
}
string NguoiQuanTro::KeyDo(int i){
     return a[i].getKeyDo();
}
string NguoiQuanTro::KeyDoComputer(){
    return c.getKeyDo();
}
string NguoiQuanTro::KeyDoanComputer(){
    return c.getKeyDoan();
}
int NguoiQuanTro::checkKey(int i, int mode, int *b){
    string keyUser1 = a[0].getKeyDo();
    if(mode == 1){
            string keyUser2 = a[1].getKeyDo(); 
            if(i==0){
                return L.CheckKeyDoan(a[0].getKeyDoan(), keyUser2, b);
            }else if(i==1){
                return L.CheckKeyDoan(a[1].getKeyDoan(), keyUser1, b);
            }
    }else{
            string keyUser2 = c.getKeyDo();;
            if(i==0){
                return L.CheckKeyDoan(a[0].getKeyDoan(), keyUser2, b);
            }else if(i==3){
                return L.CheckKeyDoan(c.getKeyDoan(), keyUser1, b);
            }

    }
    return 0;
}
// ======================= VÒNG CHƠI CHÍNH ==========================
void NguoiQuanTro::play() {
    this->mode =0;
    this->Winner = 0;
    this->hamTaoKey();
    string keyUser1;
    string keyUser2;
    while(this->Winner == 0){
        if(mode == 1){
            cout<<"User 1 KeyDoan: ";
            // neu khong dung goi y: cho nhap
            a[0].nhapKeyDoan();
            cout<<"Computer: ";
            c.nhapKeyDoan();
            cout<< c.getKeyDoan();
            keyUser2 = c.getKeyDo(); 
        }else{
            cout<<"User 1 KeyDoan: ";
            // neu khong dung goi y: cho nhap
            a[0].nhapKeyDoan();
            cout<<"User 2 KeyDoan: ";
            a[1].nhapKeyDoan();
            keyUser2 = a[1].getKeyDo();
        }
        keyUser1 = a[0].getKeyDo();
        int check ;
        if(mode == 1){
            check =0;
            L.ketQua(a[0].getKeyDoan(), keyUser2,check);
            if(check ==1) Winner ++;
            check = 0;
            L.ketQua(c.getKeyDoan(), keyUser1, check);
            if(check ==1) Winner ++;
            if(Winner ==1 && check ==0){
                Winner = 1;
            }else if(Winner ==1 && check == 1){
                Winner = 2;
            }else if(Winner == 2 && check == 1){
                Winner = 3;
            }else Winner = 0;
        }else{
            check =0;
            L.ketQua(a[0].getKeyDoan(), keyUser2,check);
            if(check ==1) Winner ++;
            check = 0;
            L.ketQua(a[1].getKeyDoan(), keyUser1, check);
            if(check ==1) Winner ++;
            if(Winner ==1 && check ==0){
                Winner = 1;
            }else if(Winner ==1 && check == 1){
                Winner = 2;
            }else if(Winner == 2 && check == 1){
                Winner = 3;
            }else Winner = 0;
        }
        
    }
}
/*Phần này viết vào GUI tạo giao diện*/
// ======================= KẾT THÚC ==========================
void NguoiQuanTro::ketThucVan() {
    if(Winner == 1){
        cout<< "User 1 win"<<endl;
    }else if(Winner == 2) {
        if(mode = 1){
            cout<< "Computer 1 win"<<endl;
        }else {
            cout<< "User 2 win"<<endl;
        }
    }else if(Winner ==3){
        cout<<"Hoa"<<endl;
    }else if(Winner == 0){
        cout<<"Hoa"<<endl;
    }
}

// ======================= CHƠI LẠI ==========================
int NguoiQuanTro::resetGame() {
    char c;
    cout << "\nBan muon choi lai khong (y/n)? ";
    cin >> c;
    cin.ignore();
    if (c == 'y' || c == 'Y') {
        return 1;
    } else {
        cout << "Cam on ban da choi!\n";
        return 0;
    }
}/*
void NguoiQuanTro::Game(){
    this->hamTaoCacNguoiChoi();
    this->chonLevel(lv);
    do{
        this->play();
        this->ketThucVan(); 
    }while (this->resetGame()==1);
    
}*/
int NguoiQuanTro::getMaxLength(){
    return this->maxLength;
}