#include "bgpch.h"
#include "ActivationLayer.h"

ActivationLayer::ActivationLayer(
    std::function<Eigen::MatrixXd(const Eigen::MatrixXd&)> activation,
    std::function<Eigen::MatrixXd(const Eigen::MatrixXd&)> activation_derivative)
    : activation(activation), activation_derivative(activation_derivative) {}

Eigen::MatrixXd ActivationLayer::forward_propagation(const Eigen::MatrixXd& input_data)
{
    input = new Eigen::MatrixXd(input_data);
    output = new Eigen::MatrixXd(activation(*input));
    return *output;
}

// Returns dE/dX (input error) for a given dE/dY (output error).
Eigen::MatrixXd ActivationLayer::backward_propagation(const Eigen::MatrixXd& output_error_data, double /*learning_rate*/)
{
    return activation_derivative(*input).array() * output_error_data.array();
}





