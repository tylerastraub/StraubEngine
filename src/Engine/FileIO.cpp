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