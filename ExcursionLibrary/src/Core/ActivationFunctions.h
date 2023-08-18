#pragma once
#include <cmath>
#include "Dense"

inline Eigen::MatrixXd tanh(const Eigen::MatrixXd& x)
{
    // Applies the hyperbolic tangent function element-wise to the input matrix using Eigen's unaryExpr method with a lambda expression.
    // tanh = (e^x - e^-x) / (e^x + e^-x)
    return x.unaryExpr([](double val) { return std::tanh(val); });
}

inline Eigen::MatrixXd tanh_derivative(const Eigen::MatrixXd& x)
{
    // Applies the derivative of the hyperbolic tangent function element-wise to the input matrix using Eigen's unaryExpr method with a lambda expression.
    // tanh' = 1 - tanh^2
    return x.unaryExpr([](double val) {return 1 - std::pow(std::tanh(val), 2); });
}
