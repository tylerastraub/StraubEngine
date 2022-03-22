#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>

class FileIO {
public:
    FileIO() = default;
    ~FileIO() = default;

    static std::vector<std::string> readFile(std::string path);

private:

};

#endif