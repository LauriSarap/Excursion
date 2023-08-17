#include "bgpch.h"
#include "Activation.h"

namespace Core
{
    std::vector<double> Activation::Apply(const std::vector<double>& input, ActivationType type)
    {
        std::vector<double> result(input.size());

        switch (type)
        {
            case ActivationType::Sigmoid:
                for (size_t i = 0; i < input.size(); i++)
                {
                    result[i] = Sigmoid(input[i]);
                }
                break;
            
            case ActivationType::Tanh:
                for (size_t i = 0; i < input.size(); i++)
                {
                    result[i] = Tanh(input[i]);
                }
                break;
            
            case ActivationType::ReLU:
                for (size_t i = 0; i < input.size(); i++)
                {
                    result[i] = ReLU(input[i]);
                }
                break;
            
            case ActivationType::Softmax:
                result = Softmax(input);
                break;

            default:
                throw std::invalid_argument("Invalid activation type");
        }
        return result;
    }

    std::vector<double> Activation::ApplyDerivative(const std::vector<double>& input, ActivationType type)
    {
        std::vector<double> result(input.size());
        
        switch (type)
        {
            case ActivationType::Sigmoid:
                for (size_t i = 0; i < input.size(); i++)
                {
                    result[i] = SigmoidDerivative(input[i]);
                }
                break;
            
            case ActivationType::Tanh:
                for (size_t i = 0; i < input.size(); i++)
                {
                    result[i] = TanhDerivative(input[i]);
                }
                break;

            case ActivationType::ReLU:
                for (size_t i = 0; i < input.size(); i++)
                {
                    result[i] = ReLUDerivative(input[i]);
                }
                break;

            /*case ActivationType::Softmax:
                result = SoftmaxDerivative(input);
                break;*/

            default:
                throw std::invalid_argument("Invalid activation type");
        }

        return result;
    }

    double Activation::Sigmoid(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }

    double Activation::SigmoidDerivative(double x)
    {
        return Sigmoid(x) * (1.0 - Sigmoid(x));
    }

    double Activation::Tanh(double x)
    {
        return std::tanh(x);
    }

    double Activation::TanhDerivative(double x)
    {
        return 1.0 - std::pow(Tanh(x), 2);
    }

    double Activation::ReLU(double x)
    {
        return x > 0 ? x : 0;
    }

    double Activation::ReLUDerivative(double x)
    {
        return x > 0 ? 1 : 0;
    }

    std::vector<double> Activation::Softmax(const std::vector<double> &x)
    {
        std::vector<double> result(x.size());

        double maxElement = *std::max_element(x.begin(), x.end());
        double sumExp = 0.0;

        for (size_t i = 0; i < x.size(); i++)
        {
            // Subtracting maxElement to scale down the values in order to avoid overflow
            result[i] = std::exp(x[i] - maxElement);
            sumExp += result[i];
        }

        // Normalize the result
        for (size_t i = 0; i < x.size(); i++)
        {
            result[i] /= sumExp;
        }

        return result;
    }
}
