#include "../header/NguoiQuanTro.h"
#include <cstdlib>
#include <ctime>

NguoiQuanTro::NguoiQuanTro() {
    diemNguoi1 = diemNguoi2 = 0;
    mode = 1;
    maxLength = 4;
    keyBiMat = "";
    srand((unsigned)time(nullptr));
}

// ======================= NGƯỜI CHƠI ==========================
void NguoiQuanTro::firstUser() {
    cout << "\n=== TAO NGUOI CHOI 1 ===\n";
    a[0].nhapTen();
    a[0].taoID();
}

void NguoiQuanTro::secondUser() {
    cout << "\nBan muon choi voi may hay nguoi khac?\n";
    cout << "1. May tinh\n2. Nguoi choi thu 2\nChon: ";
    cin >> mode;
    cin.ignore();

    if (mode == 2) {
        cout << "\n=== TAO NGUOI CHOI 2 ===\n";
        a[1].nhapTen();
        a[1].taoID();
    } else {
        cout << "\n=== CHOI VOI MAY ===\n";
        c.nhapTen();
    }
}

// ======================= CHỌN LEVEL ==========================
void NguoiQuanTro::chonLevel() {
    int lv;
    cout << "\nChon muc do choi:\n";
    cout << "1. De (toan so, nhieu goi y)\n";
    cout << "2. Trung binh (toan so, it goi y)\n";
    cout << "3. Kho (chu + so, 1 goi y)\n";
    cout << "Lua chon: ";
    cin >> lv;
    cin.ignore();

    if (lv < 1 || lv > 3) lv = 1;
    L.createLevel(lv, 3 + lv); // dễ=4, tb=5, khó=6 ký tự
    maxLength = L.getMaxLength();
    cout << "Ban da chon Level " << lv << " - Key " << maxLength << " ky tu.\n";
}

// ======================= TẠO KEY ==========================
void NguoiQuanTro::hamTaoCacNguoiChoi() {
    cout << "\n=== TAO KEY ===\n";
    if (mode == 1) { // Người vs Máy
        c.taoKeyNgauNhien(maxLength);
        keyBiMat = c.getKey();
    } else { // Người vs Người
        a[1].taoKey();
        keyBiMat = a[1].getKey();
        system("cls"); // ẩn key để người 1 không thấy
    }
    cout << "Key bi mat da duoc tao. Bat dau doan!\n";
}

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

// ======================= LỊCH SỬ ==========================
void NguoiQuanTro::showHistory() {
    if (history.empty()) return;
    cout << "\n--- Lich su doan ---\n";
    for (size_t i = 0; i < history.size(); ++i) {
        cout << i + 1 << ". " << history[i] << endl;
    }
}

// ======================= VÒNG CHƠI CHÍNH ==========================
void NguoiQuanTro::play() {
    history.clear();
    string guess;
    int luot = 4 + (3 - L.getLevelId()); // dễ 6, tb 5, khó 4 lượt

    cout << "\n=== BAT DAU TRO CHOI ===\n";
    cout << "Key co do dai " << maxLength << " ky tu.\n";
    cout << "Ban co " << luot << " luot doan.\n";

    while (luot-- > 0) {
        cout << "\nNhap key ban doan: ";
        getline(cin, guess);
        history.push_back(guess);

        if (guess == keyBiMat) {
            cout << "\nChinh xac! Ban da doan dung KEY!\n";
            diemNguoi1++;
            break;
        } else {
            cout << "Sai roi!\n";
            showHint(guess);
            showHistory();
            cout << "Con " << luot << " luot.\n";
        }
    }

    if (luot < 0) {
        cout << "\nHet luot! Key dung la: " << keyBiMat << endl;
    }

    ketThucVan();
}

// ======================= KẾT THÚC ==========================
int NguoiQuanTro::ketThucVan() {
    cout << "\n=== KET THUC VAN CHOI ===\n";
    cout << "Diem cua nguoi 1: " << diemNguoi1 << endl;
    if (mode == 2)
        cout << "Diem cua nguoi 2: " << diemNguoi2 << endl;

    resetGame();
    return diemNguoi1;
}

// ======================= CHƠI LẠI ==========================
void NguoiQuanTro::resetGame() {
    char c;
    cout << "\nBan muon choi lai khong (y/n)? ";
    cin >> c;
    cin.ignore();
    if (c == 'y' || c == 'Y') {
        chonLevel();
        hamTaoCacNguoiChoi();
        play();
    } else {
        cout << "Cam on ban da choi!\n";
    }
}
