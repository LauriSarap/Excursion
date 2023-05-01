#include <iostream>
#include <BrainGridLibrary.h>

int main()
{
    std::vector<size_t> layerSize = { 2, 2, 1 };
    std::vector<Core::ActivationType> activationFunctions = { Core::ActivationType::Sigmoid, Core::ActivationType::Sigmoid };
    double learningRate = 0.1;
    int epochs = 10000;
    Models::FeedforwardNetwork network(layerSize, activationFunctions, learningRate);

    // Train the network on the XOR problem
    std::vector<std::vector<double>> inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    std::vector<double> targets = {{0}, {1}, {1}, {0}};

    for (int i = 0; i < epochs; i++)
    {
        double totalLoss = 0.0;
        
        for (int j = 0; j < inputs.size(); j++)
        {
            auto output = network.ForwardPropagate(inputs[j]);
            
            //auto error = Core::VectorSubtraction(targets[j], output);

            // Compute loss
            double loss = 0.5 * std::pow(output[0] - targets[j], 2);
            totalLoss += loss;
            
            // Compute gradients
            std::vector<double> gradients = {output[0] - targets[j]};
            
            network.BackPropagate(gradients);

            if (i % 1000 == 0)
            {
                std::cout << "Epoch " << i << ", loss: " << totalLoss << std::endl;
            }
        }
    }

    // Test the network on the XOR problem
    for (int i = 0; i < inputs.size(); i++)
    {
        auto output = network.ForwardPropagate(inputs[i]);
        std::cout << inputs[i][0] << " XOR " << inputs[i][1] << " = " << output[0] << std::endl;
    }


    
    return 0;
}
