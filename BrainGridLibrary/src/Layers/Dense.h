#pragma once

#include "Core/Core.h"

namespace Layers
{
    class Dense
    {
    public:
        Dense(size_t inputSize, size_t outputSize, Core::ActivationType activationFunction);
        std::vector<double> Forward(const std::vector<double>& inputs);
        std::vector<double> Backward(const std::vector<double>& gradients, double learningRate);

    private:
        std::vector<double> weights;
        std::vector<double> biases;
        std::vector<double> inputCache;
        std::vector<double> outputCache;
        Core::ActivationType activationFunction;
    };
}
