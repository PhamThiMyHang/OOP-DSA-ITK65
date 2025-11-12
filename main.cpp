#include <iostream>
#include <limits>
#include "People/People.h"
#include "Computer/Computer.h"
using namespace std;

int main() {
    while (true) {
        cout << "===== TRO CHOI DOAN KEY =====\n";
        cout << "1. Choi voi nguoi\n";
        cout << "2. Choi voi may\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            // 2 người chơi
            People p1, p2;
            cout << "\n--- Nguoi choi 1 tao ---\n";
            p1.nhapTen();
            p1.taoID();
            p1.taoKey();
            p1.luuKey();
            // clear màn hình nếu muốn
            // system("cls") hoặc system("clear")

            cout << "\n--- Nguoi choi 2 doan ---\n";
            p2.nhapTenDoan();
            p2.doanKey(p1.getKey());
        }
        else if (choice == 2) {
            // người vs máy
            People p;
            Computer c;
            cout << "\n--- Nguoi choi tao key ---\n";
            p.nhapTen();
            p.taoID();
            p.taoKey();
            p.luuKey();
            // clear màn hình nếu muốn

            cout << "\n--- May tinh doan ---\n";
            c.nhapTen();
            c.doanKey(p.getKey());
        }
        else if (choice == 0) {
            cout << "Thoat chuong trinh. Bye!\n";
            break;
        }
        else {
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }

        cout << "\n";
    }
    return 0;
}
