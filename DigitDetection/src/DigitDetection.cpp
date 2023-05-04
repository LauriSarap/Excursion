#include <iostream>
#include <BrainGridLibrary.h>

int main()
{
    std::vector<std::vector<double>> inputs = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
    std::vector<double> outputs = {0, 1, 1, 0};

    Layers::Dense layer1(2, 2, Core::ActivationType::Sigmoid);
    Layers::Dense layer2(2, 1, Core::ActivationType::Sigmoid);

    layer1.InitializeWeights();
    layer2.InitializeWeights();

    int epochs = 10000;
    double learningRate = 0.1;

    for (int epoch = 0; epoch < epochs; epoch++)
    {
        double totalLoss = 0;

        for (int i = 0; i < inputs.size(); i++)
        {
            // Forward pass
            std::vector<double> layer1Output = layer1.Forward(inputs[i]);
            std::vector<double> layer2Output = layer2.Forward(layer1Output);

            std::vector<double> outputVectorForMSE = {outputs[i]};
            
            totalLoss += Core::MeanSquaredError(layer2Output, outputVectorForMSE);

            // Backward pass
            std::vector<double> layer2Gradients = {layer2Output[0] - outputs[i]};
            std::vector<double> layer1Gradients = layer2.Backward(layer1Output, layer2Gradients, learningRate);
            layer1.Backward(inputs[i], layer1Gradients, learningRate);
        }

        // Display the loss every 500 epochs
        if (epoch % 10 == 0) {
            std::cout << "Epoch: " << epoch << ", Loss: " << totalLoss / inputs.size() << std::endl;
        }
    }

    // Test the trained model
    for (auto &input : inputs) {
        std::vector<double> layer1Output = layer1.Forward(input);
        std::vector<double> layer2Output = layer2.Forward(layer1Output);

        std::cout << "Input: (" << input[0] << ", " << input[1] << "), Output: " << layer2Output[0] << std::endl;
    }

    
    // Wait for user input
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();
    
    return 0;
}
