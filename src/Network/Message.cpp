#include "Message.h"

Message::Message(std::vector<uint8_t> data) : _data(data) {}

void Message::setData(std::vector<uint8_t> data) {
    _data = data;
}

std::vector<uint8_t> Message::getData() {
    return _data;
}