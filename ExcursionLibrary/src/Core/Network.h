#pragma once
#include "Layer.h"
#include "Data/ParameterSaver.h"

class Network
{
public:
    Network();

    void add(Layer* layer);

    void use(std::function<double(const Eigen::MatrixXd&, const Eigen::MatrixXd&)> loss,
             std::function<Eigen::MatrixXd(const Eigen::MatrixXd&, const Eigen::MatrixXd&)> loss_derivative);

    std::vector<Eigen::MatrixXd> predict_outputs(const std::vector<Eigen::MatrixXd>& input_data);

    void train(const std::vector<Eigen::MatrixXd>& x_train, const std::vector<Eigen::MatrixXd>& y_train, int epochs, double learning_rate);

    void save(const std::string& filename, const std::string& path, const Data::FileType& fileType);

    void load(const std::string& filename, const std::string& path, const Data::FileType& fileType);

    std::vector<Layer*> layers;
private:
    std::function<double(const Eigen::MatrixXd&, const Eigen::MatrixXd&)> loss;
    std::function<Eigen::MatrixXd(const Eigen::MatrixXd&, const Eigen::MatrixXd&)> loss_derivative;
    
};
