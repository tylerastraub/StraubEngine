#pragma once

#include <vector>
#include <cstdint>

class Message {
public:
    Message() = default;
    Message(std::vector<uint8_t> data);
    ~Message() = default;

    void setData(std::vector<uint8_t> data);

    std::vector<uint8_t> getData();

private:
    std::vector<uint8_t> _data;

};