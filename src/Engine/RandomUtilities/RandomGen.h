#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>

class RandomGen {
public:
    RandomGen();
    ~RandomGen() = default;

    static void setSeed(unsigned int seed);

    // Returns a random int in the range [min, max]
    static int getRandomInt(int min, int max);
    // Returns a random int using the random library's uniform_int_distribution
    static int getRandomInt(std::uniform_int_distribution<int> dist);

private:
    static std::mt19937 randEng;
};

#endif