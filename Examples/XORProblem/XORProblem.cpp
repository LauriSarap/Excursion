#include <iostream>
#include <ExcursionLibrary.h>


int main()
{
    // Hyper parameters
    constexpr int epochs = 1000;
    constexpr double learning_rate = 0.09;
    
    // Training data
    std::vector<Eigen::MatrixXd> x_train =
    {
        (Eigen::MatrixXd(1, 2) << 0, 0).finished(),
        (Eigen::MatrixXd(1, 2) << 0, 1).finished(),
        (Eigen::MatrixXd(1, 2) << 1, 0).finished(),
        (Eigen::MatrixXd(1, 2) << 1, 1).finished()
    };

    std::vector<Eigen::MatrixXd> y_train
    {
        (Eigen::MatrixXd(1, 1) << 0).finished(),
        (Eigen::MatrixXd(1, 1) << 1).finished(),
        (Eigen::MatrixXd(1, 1) << 1).finished(),
        (Eigen::MatrixXd(1, 1) << 0).finished()
    };

    // Network construction
    Network net;
    net.add(new FCLayer(2, 3));
    net.add(new ActivationLayer(tanh_function, tanh_derivative));
    net.add(new FCLayer(3, 1));
    net.add(new ActivationLayer(tanh_function, tanh_derivative));

    std::cout << net.layers[0]->weights << std::endl;

    
    // Training
    net.use(mse, mse_derivative);
    net.train(x_train, y_train, epochs, learning_rate);

    //net.load("parameters", "", Data::FileType::json);
    
    // Testing
    auto out = net.predict_outputs(x_train);
    for (const auto& prediction : out)
    {
        std::cout << prediction << std::endl;
    }

    net.save("parameters", "", Data::FileType::json);
    
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();
    
    return 0;
}
