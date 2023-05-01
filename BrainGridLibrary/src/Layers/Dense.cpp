#include "bgpch.h"
#include "Dense.h"

namespace Layers
{
    Dense::Dense(size_t inputSize, size_t outputSize, Core::ActivationType activationFunction) : activationFunction(activationFunction)
    {
        // Initialize weights and biases
        weights.resize(inputSize * outputSize);
        biases.resize(outputSize);

        // Randomly initialize weights
        for (size_t i = 0; i < weights.size(); i++)
        {
            weights[i] = Core::Random::NormalDistribution(0.0, 0.01);
        }

        // Initialize biases to 0
        for (size_t i = 0; i < biases.size(); i++)
        {
            biases[i] = 0.0;
        }
    }

    std::vector<double> Dense::Forward(const std::vector<double>& inputs)
    {
        inputCache = inputs;
        auto linearOutput = Core::MatrixVectorProduct(Core::VectorToMatrix(weights, biases.size(), inputs.size()), inputs);
        linearOutput = Core::VectorAddition(linearOutput, biases);
        outputCache = Core::Activation::Apply(linearOutput, activationFunction);
        return outputCache;
    }

    std::vector<double> Dense::Backward(const std::vector<double>& gradients, double learningRate)
    {
        std::vector<double> dZ = Core::VectorHadamardProduct(Core::Activation::ApplyDerivative(outputCache, activationFunction), gradients);
        std::vector<double> dW = Core::FlattenedOuterProduct(dZ, inputCache);
        std::vector<double> dB = dZ;
        std::vector<double> dA = Core::MatrixVectorProduct(Core::MatrixTransposition(Core::VectorToMatrix(weights, biases.size(), inputCache.size())), dZ);

        // Update weights and biases
        for (size_t i = 0; i < weights.size(); i++)
        {
            weights[i] -= learningRate * dW[i];
        }

        for (size_t i = 0; i < biases.size(); i++)
        {
            biases[i] -= learningRate * dB[i];
        }
        return dA;
    }
}
