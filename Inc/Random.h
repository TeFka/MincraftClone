#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <ctime>
#include <random>

template <class REngine = std::mt19937> class Random
{
public:
    Random(int n = std::time(nullptr))
    {
        randomEngine.seed(n);
    }

    Random& get()
    {
        static Random<> r;
        return r;
    }

    int intInRange(int low, int high)
    {
        std::uniform_int_distribution<int> dist(low, high);
        return dist(randomEngine);
    }

    void setSeed(int seed)
    {
        randomEngine.seed(seed);
    }

private:
    REngine randomEngine;
};

#endif // RANDOM_H_INCLUDED
