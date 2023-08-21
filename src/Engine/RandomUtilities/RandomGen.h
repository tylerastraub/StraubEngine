#pragma once

#include <random>

/**
 * Use the following line of code ONCE in desired file to instantiate random seed:
 * std::mt19937 RandomGen::randEng{(unsigned int) std::chrono::system_clock::now().time_since_epoch().count()};
*/

class RandomGen {
public:
    RandomGen() = default;
    ~RandomGen() = default;

    static void setSeed(unsigned int seed);

    // Returns a random int in the range [min, max]
    static int getRandomInt(int min, int max);
    // Returns a random int using the random library's uniform_int_distribution
    static int getRandomInt(std::uniform_int_distribution<int> dist);

private:
    static std::mt19937 randEng;
};