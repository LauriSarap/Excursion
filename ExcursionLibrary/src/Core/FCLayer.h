#pragma once
#include "Layer.h"

class FCLayer : public Layer
{
public:
    FCLayer(int input_size, int output_size);
    virtual Eigen::MatrixXd forward_propagation(const Eigen::MatrixXd& input_data) override;
    virtual Eigen::MatrixXd backward_propagation(const Eigen::MatrixXd& output_error_data, double learning_rate) override;
};
