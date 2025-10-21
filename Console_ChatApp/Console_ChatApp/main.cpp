#include "Chat.h"
#include <iostream>

int main() 
{
    setlocale(LC_ALL, "");

    Chat chat;
    while (true) {
        try {
            std::cout << "\n1. Регистрация\n2. Вход\n3. Личное сообщение\n4. Сообщение всем\n5. Показать сообщения\n0. Выход\nВыбор: ";
            int choice;
            std::cin >> choice;
            switch (choice) {
            case 1: chat.registerUser(); break;
            case 2: chat.loginUser(); break;
            case 3: chat.sendMessageToUser(); break;
            case 4: chat.sendMessageToAll(); break;
            case 5: chat.showMessages(); break;
            case 0: return 0;
            default: std::cout << "Неверный выбор.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
}
