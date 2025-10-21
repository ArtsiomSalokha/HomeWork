#pragma once
#include <string>

class User {
public:
    User();
    User(const std::string& login, const std::string& password, const std::string& name);

    std::string getLogin() const;
    std::string getPassword() const;
    std::string getName() const;

private:
    std::string login;
    std::string password;
    std::string name;
};
