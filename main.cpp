#include "header/NguoiQuanTro.h"

#include <iostream>
using namespace std;

#include <limits>
using namespace std;

int main() {
    NguoiQuanTro quanTro;
    int choice;

    while (true) {
        cout << "==============================\n";
        cout << "       TRO CHOI DOAN KEY      \n";
        cout << "==============================\n";
        cout << "1. Choi voi nguoi\n";
        cout << "2. Choi voi may\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "\nTam biet! Hen gap lai.\n";
            break;
        }
        else if (choice == 1 || choice == 2) {
            // --- Chuẩn bị ---
            cout << "\n=== TAO NGUOI CHOI 1 ===\n";
            quanTro.firstUser();

            // chọn đối thủ
            if (choice == 2) {
                // Chơi với máy
                cout << "\n=== CHOI VOI MAY ===\n";
                quanTro.secondUser(); // mode = 1 (mặc định)
            } else {
                // Chơi với người
                quanTro.secondUser(); // mode = 2
            }

            // chọn cấp độ
            quanTro.chonLevel();

            // tạo key tương ứng
            quanTro.hamTaoCacNguoiChoi();

            // chơi chính
            quanTro.play();
        }
        else {
            cout << "\nLua chon khong hop le. Moi nhap lai!\n";
        }

        cout << "\nBan co muon tiep tuc choi khong (y/n)? ";
        char again;
        cin >> again;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (again != 'y' && again != 'Y') {
            cout << "\nCam on ban da tham gia tro choi!\n";
            break;
        }
    }

    return 0;
}
