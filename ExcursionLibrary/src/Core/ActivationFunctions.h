#pragma once
#include <cmath>
#include "Dense"

inline Eigen::MatrixXd tanh_function(const Eigen::MatrixXd& x)
{
    // Applies the hyperbolic tangent function element-wise to the input matrix using Eigen's unaryExpr method with a lambda expression.
    // tanh_function = (e^x - e^-x) / (e^x + e^-x)
    return x.unaryExpr([](double val) { return std::tanh(val); });
}

inline Eigen::MatrixXd tanh_derivative(const Eigen::MatrixXd& x)
{
    // Applies the derivative of the hyperbolic tangent function element-wise to the input matrix using Eigen's unaryExpr method with a lambda expression.
    // tanh_function' = 1 - tanh_function^2
    return x.unaryExpr([](double val) { return 1 - std::pow(std::tanh(val), 2); });
}

inline Eigen::MatrixXd sigmoid_function(const Eigen::MatrixXd& x)
{
    // Applies the sigmoid function element-wise to the input matrix using Eigen's unaryExpr method with a lambda expression.
    // sigmoid_function = 1 / (1 + e^-x)
    return x.unaryExpr([](double val) { return 1 / (1 + std::exp(-val)); });
}

inline Eigen::MatrixXd sigmoid_derivative(const Eigen::MatrixXd& x)
{
    return x.unaryExpr([](double val)
    {
        double sigmoid = 1 / (1 + std::exp(-val));
        return sigmoid * (1 - sigmoid);
    });
}

inline Eigen::MatrixXd relu_function(const Eigen::MatrixXd& x)
{
    return x.unaryExpr([](double val) { return std::max(0.0, val); });
}

inline Eigen::MatrixXd relu_derivative(const Eigen::MatrixXd& x)
{
    return x.unaryExpr([](double val) { return val > 0.0 ? 1.0 : 0.0; });
}

inline Eigen::MatrixXd leaky_relu_function(const Eigen::MatrixXd& x)
{
    return x.unaryExpr([](double val) { return val >= 0 ? val : 0.01 * val; });
}

inline Eigen::MatrixXd leaky_relu_derivative(const Eigen::MatrixXd& x)
{
    return x.unaryExpr([](double val) { return val >= 0 ? 1.0 : 0.01; });
}


