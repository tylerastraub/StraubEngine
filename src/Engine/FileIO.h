#pragma once

#include <vector>
#include <string>

class FileIO {
public:
    FileIO() = default;
    ~FileIO() = default;

    static std::vector<std::string> readFile(std::string path);
    static void writeFile(std::string path, std::vector<std::string> contents);

private:

};