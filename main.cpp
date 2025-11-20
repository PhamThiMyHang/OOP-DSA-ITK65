#include <SFML/Graphics.hpp>   // Thư viện đồ họa SFML (vẽ hình, cửa sổ, nút bấm...)
#include <iostream>            // Để in ra console (dùng std::cout)
#include "Menu.h"               // File header tự viết – chứa toàn bộ menu game
#include "header/NguoiQuanTro.h"

#include <iostream>
using namespace std;

#include <limits>
using namespace std;

int main() {
    // 1. TẠO CỬA SỔ GAME
    // ──────────────────────────────────────────────────────────────
    sf::RenderWindow window(sf::VideoMode(900, 600),"Guess Arena");

    window.setFramerateLimit(60);   

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visible(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visible));

                menu.resize(event.size.width, event.size.height);
            }

            // Gửi tất cả sự kiện cho class Menu xử lý (hover, click nút, cuộn chuột...)
            menu.handleEvent(window, event);
        }

        menu.update();

        window.clear(sf::Color(12, 12, 40));   // Xóa màn hình cũ, tô màu nền xanh vũ trụ

        menu.draw(window);                     // Vẽ toàn bộ menu (nút, chữ, nền...)

        window.display();                      // Hiển thị lên màn hình (double buffering)
    }

    return 0; // Kết thúc chương trình thành công
}