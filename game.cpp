#include <SFML/Graphics.hpp>   // Thư viện đồ họa SFML (vẽ hình, cửa sổ, nút bấm...)
#include <iostream>            // Để in ra console (dùng std::cout)
#include "Menu.h"               // File header tự viết – chứa toàn bộ menu game

int main() {
    // ──────────────────────────────────────────────────────────────
    // 1. TẠO CỬA SỔ GAME
    // ──────────────────────────────────────────────────────────────
    sf::RenderWindow window(
        sf::VideoMode(900, 600),                  // Kích thước cửa sổ: 900x600
        "Guess Arena",                            // Tên game hiện trên thanh tiêu đề
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize // Có thanh tiêu đề, nút đóng, và cho phép resize
    );

    window.setFramerateLimit(60);   // Giới hạn 60 khung hình/giây → mượt mà, không tốn CPU

    // ──────────────────────────────────────────────────────────────
    // 2. KHỞI TẠO MENU
    // ──────────────────────────────────────────────────────────────
    Menu menu(window.getSize().x, window.getSize().y);
    // Truyền kích thước cửa sổ vào để menu tự động co giãn đẹp khi đổi kích thước

    // ──────────────────────────────────────────────────────────────
    // 3. VÒNG LẶP CHÍNH CỦA GAME (chạy liên tục đến khi thoát)
    // ──────────────────────────────────────────────────────────────
    while (window.isOpen()) {
        sf::Event event;

        // Xử lý mọi sự kiện xảy ra trong frame này (bấm chuột, bàn phím, resize, đóng cửa sổ...)
        while (window.pollEvent(event)) {

            // Người chơi bấm nút X hoặc Alt+F4 → thoát game
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Khi người chơi kéo to/thu nhỏ cửa sổ
            if (event.type == sf::Event::Resized) {
                // Cập nhật lại vùng nhìn để hình không bị méo
                sf::FloatRect visible(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visible));

                // Thông báo cho menu biết cửa sổ đã thay đổi → tự co giãn chữ, nút bấm...
                menu.resize(event.size.width, event.size.height);
            }

            // Gửi tất cả sự kiện cho class Menu xử lý (hover, click nút, cuộn chuột...)
            menu.handleEvent(window, event);
        }

        // Cập nhật các hiệu ứng động: nhấp nháy logo, hiệu ứng hover nút...
        menu.update();

        // ──────────────────────────────────────────────────────────────
        // Kiểm tra xem người chơi đã chọn xong chế độ + độ khó chưa
        // ──────────────────────────────────────────────────────────────
        if (menu.getState() == GAME_PVP || menu.getState() == GAME_PVC) {
            // In ra console để test (sau này sẽ chuyển sang màn hình chơi thật)
            std::cout << "=== BẮT ĐẦU TRẬN ĐẤU ===\n";
            std::cout << "Cấp độ: " 
                      << (menu.level == 0 ? "DỄ" : menu.level == 1 ? "TRUNG BÌNH" : "KHÓ") 
                      << "\n";
            std::cout << "Chế độ: " 
                      << (menu.pvp ? "NGƯỜI VS NGƯỜI" : "NGƯỜI VS MÁY") 
                      << "\n\n";

            // Tạm thời quay lại menu chính sau khi chọn xong (sẽ thay bằng phần chơi thật sau)
            menu.reset();
        }

        // ──────────────────────────────────────────────────────────────
        // VẼ LÊN MÀN HÌNH
        // ──────────────────────────────────────────────────────────────
        window.clear(sf::Color(12, 12, 40));   // Xóa màn hình cũ, tô màu nền xanh vũ trụ

        menu.draw(window);                     // Vẽ toàn bộ menu (nút, chữ, nền...)

        window.display();                      // Hiển thị lên màn hình (double buffering)
    }

    return 0; // Kết thúc chương trình thành công
}