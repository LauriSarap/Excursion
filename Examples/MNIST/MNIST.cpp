#include <iostream>
#include <fstream>
#include <string>
#include "Dense"
#include "ExcursionLibrary.h"

#include "MNISTReader.h"

int main()
{
    // Settings
    int training_samples = 1000; // Max 60k
    int test_samples = 10; // Max 10k
    int epochs = 35;
    double learning_rate = 0.09;
    
   // Data loadings 
    std::string path = "../../Examples/MNIST";
    MNIST::MNISTData mnist_data = MNIST::read_mnist_data(path);

    std::cout << "Preprocessing MNIST training images.." << std::endl;
    // x_train is a vector with size 60k of matrices of size 784, where each row (1x784 matrix) is a flattened image.
    // TODO Make an option to load in less images, as 60k images takes 376 MB of memory.
    std::vector<Eigen::MatrixXd> x_train;
    for (int i = 0; i < training_samples; ++i) // TODO Check how this is done faster. Potentially using Eigen::Map
    {
        Eigen::MatrixXd image_vector(1, 28*28);
        for (int row = 0; row < 28; ++row)
        {
            for (int col = 0; col < 28; ++col)
            {
                // Normalize the pixel values to be of type double and be between 0 and 1.
                image_vector(0, row * 28 + col) = static_cast<double>(mnist_data.training_images[i](row, col)) / 255.0;
            }
        }

        // Assign the image vector to the i-th row of the matrix (60k rows as 60k images)
        x_train.push_back(image_vector);
    }

    std::cout << "Preprocessing MNIST training labels.." << std::endl;
    // y_train is a matrix of size (60000, 10), where each row is a one-hot vector.
    // TODO Check how to make this more memory efficient. Currently, we have 60k vectors of size 10, with data type double (8 bytes).
    // TODO This is 4.8 MB of memory. We can probably do better with smaller data types. :)
    std::vector<Eigen::MatrixXd> y_train;
    for (int i = 0; i < training_samples; ++i)
    {
        Eigen::MatrixXd label_vector = Eigen::MatrixXd::Zero(1, 10);
        label_vector(0, mnist_data.training_labels[i]) = 1.0;
        y_train.push_back(label_vector);
    }

    std::cout << "Preprocessing MNIST test images.." << std::endl;
    std::vector<Eigen::MatrixXd> x_test;
    for (int i = 0; i < test_samples; ++i) 
    {
        Eigen::MatrixXd image_vector(1, 28*28);
        for (int row = 0; row < 28; ++row)
        {
            for (int col = 0; col < 28; ++col)
            {
                // Normalize the pixel values to be of type double and be between 0 and 1.
                image_vector(0, row * 28 + col) = static_cast<double>(mnist_data.test_images[i](row, col)) / 255.0;
            }
        }

        // Assign the image vector to the i-th row of the matrix (60k rows as 60k images)
        x_test.push_back(image_vector);
    }

    std::cout << "Preprocessing MNIST test labels.." << std::endl;
    std::vector<Eigen::MatrixXd> y_test;
    for (int i = 0; i < test_samples; ++i)
    {
        Eigen::MatrixXd label_vector = Eigen::MatrixXd::Zero(1, 10);
        label_vector(0, mnist_data.test_labels[i]) = 1.0;
        y_test.push_back(label_vector);
    }

    // Network architecture
    Network net;
    net.add(new FCLayer(28*28, 100));
    net.add(new ActivationLayer(tanh_function, tanh_derivative));
    net.add(new FCLayer(100, 50));
    net.add(new ActivationLayer(tanh_function, tanh_derivative));
    net.add(new FCLayer(50, 10));
    net.add(new ActivationLayer(tanh_function, tanh_derivative));

    // Training
    net.use(mse, mse_derivative);
    net.train(x_train, y_train, epochs, learning_rate);

    // Testing
    auto out = net.predict_outputs(x_test);
    std::cout << "Predicted outputs: " << std::endl;
    for (int i = 0; i < out.size(); ++i)
    {
        std::cout << out[i] << std::endl;
    }
    std::cout << "True values: " << std::endl;
    for (int i = 0; i < y_test.size(); ++i)
    {
        std::cout << y_test[i] << std::endl;
    }

    std::cout << "Accuracy: " << std::endl;

    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();
    std::cin.get();

    return 0;
}
