#pragma once
#include "Dense"

class Layer
{
public:
    Layer() : input(nullptr), output(nullptr)
    {
        
    }

    virtual ~Layer()
    {
        delete input;
        delete output;
    }

    virtual Eigen::MatrixXd forward_propagation(const Eigen::MatrixXd& input_data) = 0;

    // Pure virtual function for backward propagation
    virtual Eigen::MatrixXd backward_propagation(const Eigen::MatrixXd& output_error_data, double learning_rate) = 0;

    Eigen::MatrixXd weights;
    Eigen::MatrixXd biases;
    
protected:
    Eigen::MatrixXd* input;
    Eigen::MatrixXd* output;
};
