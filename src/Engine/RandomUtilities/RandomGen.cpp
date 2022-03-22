#include "RandomGen.h"

#include <chrono>

void RandomGen::setSeed(unsigned int seed) {
    RandomGen::randEng.seed(seed);
}

int RandomGen::getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(RandomGen::randEng);
}

int RandomGen::getRandomInt(std::uniform_int_distribution<int> dist) {
    return dist(RandomGen::randEng);
}