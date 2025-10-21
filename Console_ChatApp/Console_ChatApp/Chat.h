#pragma once
#include "User.h"
#include "Message.h"

class Chat {
public:
    Chat();
    ~Chat();

    void registerUser();
    void loginUser();
    void sendMessageToUser();
    void sendMessageToAll();
    void showMessages();

private:
    User* users;
    int userCount;
    int userCapacity;

    Message<std::string>* messages;
    int messageCount;
    int messageCapacity;

    User* currentUser;

    void expandUsers();
    void expandMessages();
    User* findUser(const std::string& login);
};
