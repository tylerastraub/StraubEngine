#include "FileIO.h"

#include <fstream>
#include <SDL.h>

std::vector<std::string> FileIO::readFile(std::string path) {
    std::ifstream file;
    file.open(SDL_GetBasePath() + path);
    std::string currentLine;
    std::vector<std::string> result;
    while(std::getline(file, currentLine)) {
        result.push_back(currentLine);
    }

    return result;
}

void FileIO::writeFile(std::string path, std::vector<std::string> contents) {
    std::ofstream file;
    file.open(path, std::ofstream::out | std::ofstream::trunc);
    for(auto s : contents) {
        file << s << std::endl;
    }
    file.close();
}