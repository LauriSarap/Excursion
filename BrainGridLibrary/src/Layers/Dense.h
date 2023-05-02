#pragma once

#include "Core/Core.h"

namespace Layers
{
    class Dense
    {
    public:
        Dense(int inputSize, int outputSize, Core::ActivationType activationType);

        void InitializeWeights();

        std::vector<double> Forward(std::vector<double> &input);
        std::vector<double> Backward(const std::vector<double> &input, const std::vector<double> &gradients, double learningRate);

        int inputSize;
        int outputSize;
        std::vector<double> biases;
        Core::Matrix weights;

    private:
        Core::ActivationType activationType;
    };
}
