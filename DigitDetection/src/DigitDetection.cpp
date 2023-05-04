#include <iostream>
#include <BrainGridLibrary.h>

int main()
{
    std::vector<std::vector<double>> inputs = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
    std::vector<double> outputs = {0, 1, 1, 0};

    Layers::Dense layer1(2, 2, Core::ActivationType::Tanh);
    Layers::Dense layer2(2, 1, Core::ActivationType::Tanh);

    layer1.InitializeWeights();
    layer2.InitializeWeights();

    int epochs = 20000;
    double learningRate = 0.05;

    for (int epoch = 0; epoch < epochs; epoch++)
    {
        double totalLoss = 0;
        double totalError = 0;

        for (int i = 0; i < inputs.size(); i++)
        {
            // Forward pass
            std::vector<double> layer1Output = layer1.Forward(inputs[i]);
            std::vector<double> layer2Output = layer2.Forward(layer1Output);

            // Compute loss with loss function
            totalLoss += Core::MeanSquaredError(layer2Output, {outputs[i]});

            // Find the numerical error
            std::vector<double> error = {outputs[i] - layer2Output[0]};
            totalError += std::abs(error[0]);

            // Backward pass
            std::vector<double> layer2NewGradients = layer2.Backward(layer1Output, error, learningRate);
            layer1.Backward(inputs[i], layer2NewGradients, learningRate);
        }

        // Display the loss every 50 epochs
        if (epoch % 100 == 0) {
            std::cout << "Epoch: " << epoch << ", Error: " << totalError << std::endl;
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
