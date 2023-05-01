#pragma once

namespace Core
{
    class Random
    {
    public:
        static double UniformDistribution(double min, double max);
        static int UniformDistributionInt(int min, int max);
        static double NormalDistribution(double mean, double stdDev);
    };
}
