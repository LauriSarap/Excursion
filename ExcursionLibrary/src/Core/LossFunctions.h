#pragma once
#include "Dense"

inline double mse(const Eigen::MatrixXd& y_true, const Eigen::MatrixXd& y_pred)
{
    // Mean Squared Error = 1/n * sum((y_true - y_pred)^2)
    return (y_true - y_pred).array().pow(2).mean();
}

inline Eigen::MatrixXd mse_derivative(const Eigen::MatrixXd& y_true, const Eigen::MatrixXd& y_pred)
{
    // Derivative of Mean Squared Error = 2/n * (y_pred - y_true)
    return 2 * (y_pred - y_true) / y_true.size();
}

inline double binary_cross_entropy_loss(const Eigen::MatrixXd& y_true, const Eigen::MatrixXd& y_pred)
{
    Eigen::VectorXd y_pred_clamped = y_pred.unaryExpr([](double x) { return std::min(std::max(x, 1e-15), 1 - 1e-15); });

    double loss = -(y_true.array() * y_pred_clamped.array().log() + (1 - y_true.array()) * log(1 - y_pred_clamped.array())).mean();
    return loss;
}

inline Eigen::MatrixXd binary_cross_entropy_loss_derivative()
{
    
}
