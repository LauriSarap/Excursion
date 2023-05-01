#include "bgpch.h"
#include "FeedforwardNetwork.h"

namespace Models
{
    FeedforwardNetwork::FeedforwardNetwork(const std::vector<size_t>& layerSizes, const std::vector<Core::ActivationType>& activationFunctions, double lr)
    {
        if (layerSizes.size() != activationFunctions.size() + 1)
        {
            throw std::invalid_argument("The number of activation functions should be one less than the number of layer sizes.");
        }

        for (size_t i = 0; i < layerSizes.size() - 1; ++i)
        {
            layers.emplace_back(layerSizes[i], layerSizes[i + 1], activationFunctions[i]);
        }

        learningRate = lr;
    }

    std::vector<double> FeedforwardNetwork::ForwardPropagate(const std::vector<double>& input)
    {
        std::vector<double> layerOutput = input;
        
        for (auto& layer : layers)
        {
            layerOutput = layer.Forward(layerOutput);
        }
        
        return layerOutput;
    }

    void FeedforwardNetwork::BackPropagate(const std::vector<double>& gradients)
    {
        std::vector<double> layerGradients = gradients;

        for (auto it = layers.rbegin(); it != layers.rend(); ++it)
        {
            it->Backward(layerGradients, learningRate);
        }
    }
}
