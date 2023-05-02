#pragma once

namespace Core
{
    enum class ActivationType
    {
        Sigmoid,
        Tanh,
        ReLU,
        Softmax
    };
    
    class Activation
    {
    public:
        static std::vector<double> Apply(const std::vector<double>  &input, ActivationType type);
        static std::vector<double> ApplyDerivative(const std::vector<double> &input, ActivationType type);

    private:
        static double Sigmoid(double x);
        static double SigmoidDerivative(double x);

        static double Tanh(double x);
        static double TanhDerivative(double x);

        static double ReLU(double x);
        static double ReLUDerivative(double x);

        static std::vector<double> Softmax(const std::vector<double> &x);
    };
}
