#pragma once
#include <vector>

namespace Core
{
    typedef std::vector<std::vector<double>> Matrix;

    // Matrix operations
    Matrix MatrixAddition(const Matrix &a, const Matrix &b);
    Matrix MatrixSubtraction(const Matrix &a, const Matrix &b);
    Matrix MatrixMultiplication(const Matrix &a, const Matrix &b);
    Matrix MatrixScalarMultiplication(const Matrix &a, double scalar);
    Matrix MatrixTransposition(const Matrix &a);

    // Vector operations
    std::vector<double> VectorAddition (const std::vector<double> &a, const std::vector<double> &b);
    std::vector<double> VectorSubtraction(const std::vector<double> &a, const std::vector<double> &b);
    std::vector<double> VectorHadamardProduct(const std::vector<double> &a, const std::vector<double> &b);

    // Return vectors
    std::vector<double> MatrixVectorProduct(const Matrix &matrix, const std::vector<double> &vector);
    std::vector<double> FlattenedOuterProduct(const std::vector<double> &a, const std::vector<double> &b);

    // Return matrices
    Matrix VectorToMatrix(const std::vector<double> &vector, size_t rows, size_t cols);
    Matrix OuterProduct(const std::vector<double> &a, const std::vector<double> &b);

    double MeanSquaredError(const std::vector<double> &predictions, const std::vector<double> &targets);
    
}
