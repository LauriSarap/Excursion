#include "bgpch.h"
#include "Random.h"

namespace Core
{
    double Random::UniformDistribution(double min, double max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> distribution(min, max);
        return distribution(gen);
    }

    int Random::UniformDistributionInt(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(gen);
    }


    double Random::NormalDistribution(double mean, double stdDev)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::normal_distribution<double> distribution(mean, stdDev);
        return distribution(gen);
    }

}
