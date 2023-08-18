#include "bgpch.h"
#include "FCLayer.h"

FCLayer::FCLayer(int input_size, int output_size)
{
    //TODO - Initialize weights and biases through other script
    weights = Eigen::MatrixXd::Random(input_size, output_size) * 0.5;
    biases = Eigen::MatrixXd::Random(1, output_size) * 0.5;
}

Eigen::MatrixXd FCLayer::forward_propagation(const Eigen::MatrixXd& input_data)
{
    input = new Eigen::MatrixXd(input_data);
    output = new Eigen::MatrixXd(*input * weights + biases);
    return *output;
}

Eigen::MatrixXd FCLayer::backward_propagation(const Eigen::MatrixXd& output_error, double learning_rate)
{
    Eigen::MatrixXd input_error = output_error * weights.transpose();
    Eigen::MatrixXd weights_error = input->transpose() * output_error;
    
    weights -= weights_error * learning_rate;
    biases -= output_error * learning_rate;
    return input_error;
}


