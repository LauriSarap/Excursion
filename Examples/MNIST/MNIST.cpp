#include <iostream>
#include <fstream>
#include <string>
#include "Dense"
#include "ExcursionLibrary.h"

#include "MNISTReader.h"

int main()
{
    std::string path = "../../Examples/MNIST";

    MNIST::MNISTData mnist_data = MNIST::read_mnist_data(path);

    Eigen::MatrixXd x_train(mnist_data.training_images.size(), 28*28);
    Eigen::MatrixXf y_train = Eigen::MatrixXf::Zero(mnist_data.training_labels.size(), 10);
    for (int i = 0; i < mnist_data.training_images.size(); ++i)
    {
        //x_train.row(i) = Eigen::Map<Eigen::RowVectorXf>(mnist_data.training_images[i].data(), 28*28);
        y_train(i, mnist_data.training_labels[i]) = 1.0f; 
    }

    

    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}
