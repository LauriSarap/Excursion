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
