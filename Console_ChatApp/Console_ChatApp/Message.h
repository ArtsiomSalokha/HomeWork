#pragma once
#include <string>

template<typename T>
class Message {
public:
    Message() = default;
    Message(const std::string& sender, const std::string& receiver, const T& content)
        : sender(sender), receiver(receiver), content(content) {
    }

    std::string getSender() const { return sender; }
    std::string getReceiver() const { return receiver; }
    T getContent() const { return content; }

private:
    std::string sender;
    std::string receiver;
    T content;
};
