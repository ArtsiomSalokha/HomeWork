#include "Chat.h"
#include <iostream>
#include <stdexcept>

Chat::Chat()
    : users(new User[2]), userCount(0), userCapacity(2),
    messages(new Message<std::string>[2]), messageCount(0), messageCapacity(2),
    currentUser(nullptr) {
}

Chat::~Chat() {
    delete[] users;
    delete[] messages;
}

void Chat::expandUsers() {
    userCapacity *= 2;
    User* newUsers = new User[userCapacity];
    for (int i = 0; i < userCount; ++i)
        newUsers[i] = users[i];
    delete[] users;
    users = newUsers;
}

void Chat::expandMessages() {
    messageCapacity *= 2;
    Message<std::string>* newMessages = new Message<std::string>[messageCapacity];
    for (int i = 0; i < messageCount; ++i)
        newMessages[i] = messages[i];
    delete[] messages;
    messages = newMessages;
}

User* Chat::findUser(const std::string& login) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].getLogin() == login)
            return &users[i];
    }
    return nullptr;
}

void Chat::registerUser() {
    std::string login, password, name;
    std::cout << "Введите логин: ";
    std::cin >> login;
    if (findUser(login)) throw std::runtime_error("Логин уже занят.");
    std::cout << "Введите пароль: ";
    std::cin >> password;
    std::cout << "Введите имя: ";
    std::cin >> name;
    if (userCount == userCapacity) expandUsers();
    users[userCount++] = User(login, password, name);
    std::cout << "Регистрация успешна.\n";
}

void Chat::loginUser() {
    std::string login, password;
    std::cout << "Логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;
    User* user = findUser(login);
    if (!user || user->getPassword() != password)
        throw std::runtime_error("Неверный логин или пароль.");
    currentUser = user;
    std::cout << "Добро пожаловать, " << currentUser->getName() << "!\n";
}

void Chat::sendMessageToUser() {
    if (!currentUser) throw std::runtime_error("Вы не авторизованы.");
    std::string to, text;
    std::cout << "Кому отправить сообщение (логин): ";
    std::cin >> to;
    User* receiver = findUser(to);
    if (!receiver) throw std::runtime_error("Пользователь не найден.");
    std::cout << "Введите сообщение: ";
    std::cin.ignore();
    std::getline(std::cin, text);
    if (messageCount == messageCapacity) expandMessages();
    messages[messageCount++] = Message<std::string>(currentUser->getLogin(), to, text);
    std::cout << "Сообщение отправлено.\n";
}

void Chat::sendMessageToAll() {
    if (!currentUser) throw std::runtime_error("Вы не авторизованы.");
    std::string text;
    std::cout << "Введите сообщение для всех: ";
    std::cin.ignore();
    std::getline(std::cin, text);
    for (int i = 0; i < userCount; ++i) {
        if (users[i].getLogin() != currentUser->getLogin()) {
            if (messageCount == messageCapacity) expandMessages();
            messages[messageCount++] = Message<std::string>(currentUser->getLogin(), users[i].getLogin(), text);
        }
    }
    std::cout << "Сообщение отправлено всем.\n";
}

void Chat::showMessages() {
    if (!currentUser) throw std::runtime_error("Вы не авторизованы.");
    std::cout << "Ваши сообщения:\n";
    for (int i = 0; i < messageCount; ++i) {
        const auto& msg = messages[i];
        if (msg.getSender() == currentUser->getLogin() || msg.getReceiver() == currentUser->getLogin()) {
            std::cout << "[" << msg.getSender() << " → " << msg.getReceiver() << "]: " << msg.getContent() << "\n";
        }
    }
}
