#include "bgpch.h"
#include "Network.h"

Network::Network()
{
    
}

void Network::add(Layer* layer)
{
    layers.push_back(layer);
}

void Network::use(std::function<double(const Eigen::MatrixXd&, const Eigen::MatrixXd&)> loss,
                  std::function<Eigen::MatrixXd(const Eigen::MatrixXd&, const Eigen::MatrixXd&)> loss_derivative)
{
    this->loss = loss;
    this->loss_derivative = loss_derivative;
}

std::vector<Eigen::MatrixXd> Network::predict_outputs(const std::vector<Eigen::MatrixXd>& input_data)
{
    std::vector<Eigen::MatrixXd> outputs;
    for (const auto& input : input_data)
    {
        Eigen::MatrixXd output = input;
        for (auto& layer : layers) {
            output = layer->forward_propagation(output);
        }
        outputs.push_back(output);
    }
    return outputs;
}

void Network::train(const std::vector<Eigen::MatrixXd>& x_train, const std::vector<Eigen::MatrixXd>& y_train, int epochs, double learning_rate)
{
    for (int i = 0; i < epochs; ++i)
    {
        double display_error = 0;
        
        for (size_t j = 0; j < x_train.size(); ++j)
        {
            // Forward propagation
            Eigen::MatrixXd output = x_train[j];
            for (auto& layer : layers) {
                output = layer->forward_propagation(output);
            }
            
            // Computing loss for display purposes
            display_error += loss(y_train[j], output);

            // Backward propagation
            Eigen::MatrixXd error = loss_derivative(y_train[j], output);
            for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
                error = (*it)->backward_propagation(error, learning_rate);
            }
        }
        // Average error from all samples
        display_error /= x_train.size();
        std::cout << "Epoch " << (i + 1) << "/" << epochs << "   error=" << display_error << std::endl;
    }
}

void Network::save(const std::string& filename, const std::string& path, const Data::FileType& fileType)
{
    SaveWeightsAndBiases(layers, filename, path, fileType);
}

void Network::load(const std::string& filename, const std::string& path, const Data::FileType& fileType)
{
    LoadWeightsAndBiases(layers, filename, path, fileType);
}




