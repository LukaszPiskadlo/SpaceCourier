#pragma once

#include <random>

template <typename T>
class RandomNumber
{
public:
    RandomNumber(T from, T to) : generator((std::random_device())()), distribution(from, to)
    {
    }

    ~RandomNumber()
    {
    }

    T generate()
    {
        return distribution(generator);
    }

private:
    std::mt19937 generator;
    std::uniform_real_distribution<T> distribution;
};
