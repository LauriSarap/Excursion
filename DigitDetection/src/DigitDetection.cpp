#include <iostream>
#include <BrainGridLibrary.h>

int main()
{
    Layers::Dense inputLayer(2, 1, Core::ActivationType::Sigmoid);
    inputLayer.InitializeWeights();

    std::cout << "Layer weights:" << std::endl;
    
    for (int i = 0; i < inputLayer.outputSize; i++)
    {
        std::cout << "Weights of output node " << i + 1 << " ";
        
        for (int j = 0; j < inputLayer.inputSize; j++)
        {
            std::cout << inputLayer.weights[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < inputLayer.outputSize; i++)
    {
        std::cout << "Bias of output node " << i + 1 << ": " << inputLayer.biases[i] << std::endl;
    }

    std::cout << "Forwarding through the network:" << std::endl;
    std::vector<double> exampleInput = { 1, 1 };
    
    std::vector<double> output = inputLayer.Forward(exampleInput);

    for (int i = 0; i < output.size(); i++)
    {
        std::cout << "Output of node " << i + 1 << ": " << output[i] << std::endl;
    }
    
    // Wait for user input
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();
    
    return 0;
}
