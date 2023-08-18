#pragma once
#include "Layer.h"

class ActivationLayer : Layer
{
public:
    ActivationLayer(
        std::function<Eigen::MatrixXd(const Eigen::MatrixXd&)> activation,
        std::function<Eigen::MatrixXd(const Eigen::MatrixXd&)> activation_derivative);
    
    virtual Eigen::MatrixXd forward_propagation(const Eigen::MatrixXd& input_data) override;
    virtual Eigen::MatrixXd backward_propagation(const Eigen::MatrixXd& output_error_data, double learning_rate) override;

private:
    std::function<Eigen::MatrixXd(const Eigen::MatrixXd&)> activation;
    std::function<Eigen::MatrixXd(const Eigen::MatrixXd&)> activation_derivative;
};
