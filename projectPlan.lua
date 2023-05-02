BrainGrid/
|-- BrainGridLibrary/
|   |-- src/
|   |   |-- Core/
|   |   |   |-- DataHandling.cpp, DataHandling.h
|   |   |   |-- LinearAlgebra.cpp, LinearAlgebra.h
|   |   |   |   |-- Matrix MatrixAddition(Matrix &a, Matrix &b);
|   |   |   |   |-- Matrix MatrixSubtraction(Matrix &a, Matrix &b);
|   |   |   |   |-- Matrix MatrixMultiplication(Matrix &a, Matrix &b);
|   |   |   |   |-- Matrix MatrixScalarMultiplication(Matrix &a, double scalar);
|   |   |   |   |-- Matrix MatrixTransposition(Matrix &a,);
|   |   |   |   |-- vector<double> VectorAddition(vector<double> &a, vector<double> &b);
|   |   |   |   |-- vector<double> VectorSubtraction(vector<double> &a, vector<double> &b);
|   |   |   |   |-- vector<double> VectorHadamardProduct(vector<double> &a, vector<double> &b);
|   |   |   |   |-- vector<double> MatrixVectorProduct(Matrix &matrix, vector<double> &vector);
|   |   |   |   |-- vector<double> FlattenedOuterProduct(vector<double> &a, vector<double> &b);
|   |   |   |   |-- Matrix VectorToMatrix(vector<double> &a, vector<double> &b);
|   |   |   |   |-- Matrix OuterProduct(vector<double> &a, vector<double> &b);
|   |   |   |-- Random.cpp and Random.h
|   |   |   |   |-- double UniformDistribution(double min, double max);
|   |   |   |   |-- double UniformDistributionInt(int min, int max);
|   |   |   |   |-- double NormalDistribution(double mean, double std);
|   |   |   |-- Utilities.cpp, Utilities.h
|   |   |   |-- Activation.cpp, Activation.h
|   |   |   |   |-- ActivationType {Sigmoid, Tanh, ReLU, Softmax}
|   |   |   |   |-- vector<double> Apply(vector<double> &input, ActivationType type);
|   |   |   |   |-- vector<double> ApplyDerivative(vector<double> &input, ActivationType type);
|   |   |   |   |-- double Sigmoid(double x);
|   |   |   |   |-- double SigmoidDerivative(double x);
|   |   |   |   |-- double Tanh(double x);
|   |   |   |   |-- double TanhDerivative(double x);
|   |   |   |   |-- double ReLU(double x);
|   |   |   |   |-- double ReLUDerivative(double x);
|   |   |   |   |-- vector<double> Softmax(vector<double> &input);
|   |   |-- Layers/
|   |   |   |-- Dense.cpp, Dense.h
|   |   |   |   |-- Dense(size_t inputSize, size_t outputSize, ActivationType activationType);
|   |   |   |   |-- vector<double> Forward(vector<double> &inputs);
|   |   |   |   |-- vector<double> Backward(vector<double> &gradients, double learningRate);
|   |   |   |-- Convolution.cpp, Convolution.h
|   |   |   |-- Dropout.cpp, Dropout.h
|   |   |   |-- Normalization.cpp, Normalization.h
|   |   |   |-- Pooling.cpp, Pooling.h
|   |   |-- Models/
|   |   |   |-- CNN.cpp, CNN.h
|   |   |   |-- FeedforwardNetwork.cpp, FeedforwardNetwork.h
|   |   |   |   |-- FeedforwardNetwork(vector<size_t>& layerSizes, vector<ActivationType>& activationTypes, double learningRate);
|   |   |   |   |-- vector<double> ForwardPropagate(vector<double> &inputs);
|   |   |   |   |-- void BackwardPropagate(vector<double> &gradients);
|   |   |   |-- GAN.cpp, GAN.h
|   |   |   |-- GRU.cpp, GRU.h
|   |   |   |-- LSTM.cpp, LSTM.h
|   |   |   |-- RNN.cpp, RNN.h
|   |   |-- Optimization/
|   |   |   |-- Loss.cpp, Loss.h
|   |   |   |-- Optimizers.cpp, Optimizers.h
|   |   |-- Preprocessing/
|   |       |-- ImagePreprocessing.cpp, ImagePreprocessing.h
|   |       |-- GeneralPreprocessing.cpp, GeneralPreprocessing.h
|   |-- ThirdParty/
|       |-- (external libraries, if needed)
|-- DigitDetection/
|   |-- DigitDetection.cpp

