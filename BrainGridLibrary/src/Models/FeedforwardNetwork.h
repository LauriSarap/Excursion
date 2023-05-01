#pragma once
#include "Core/Activation.h"
#include "Layers/Dense.h"

namespace Models
{
    class FeedforwardNetwork
    {
    public:
        FeedforwardNetwork(const std::vector<size_t>& layerSizes, const std::vector<Core::ActivationType>& activationFunctions, double lr = 0.01);

        std::vector<double> ForwardPropagate(const std::vector<double>& input);

        void BackPropagate(const std::vector<double>& gradients);

    private:
        std::vector<Layers::Dense> layers;
        double learningRate = 0.01;
    };
}
