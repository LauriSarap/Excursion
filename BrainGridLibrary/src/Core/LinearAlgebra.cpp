#include "bgpch.h"
#include "LinearAlgebra.h"

Core::Matrix Core::MatrixAddition(const Matrix& a, const Matrix& b)
{
    size_t rows = a.size();
    size_t cols = a[0].size();

    if (rows != b.size() || cols != b[0].size()) throw std::invalid_argument("Matrices must be of the same size.");

    Matrix result(rows, std::vector<double>(cols, 0.0));

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }

    return result;
}

Core::Matrix Core::MatrixSubtraction(const Matrix& a, const Matrix& b)
{
    size_t rows = a.size();
    size_t cols = a[0].size();

    if (rows != b.size() || cols != b[0].size()) throw std::invalid_argument("Matrices must be of the same size.");

    Matrix result(rows, std::vector<double>(cols, 0.0));

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            result[i][j] = a[i][j] - b[i][j];
        }
    }

    return result;
}

Core::Matrix Core::MatrixMultiplication(const Matrix& a, const Matrix& b)
{
    size_t rowsA = a.size();
    size_t colsA = a[0].size();
    size_t rowsB = b.size();
    size_t colsB = b[0].size();

    if (colsA != rowsB) throw std::invalid_argument("Matrix dimensions must be compatible for multiplication!");

    Matrix result(rowsA, std::vector<double>(colsB, 0.0));

    for (size_t i = 0; i < rowsA; i++)
    {
        for (size_t j = 0; j < colsB; j++)
        {
            for (size_t k = 0; k < colsA; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

Core::Matrix Core::MatrixScalarMultiplication(const Matrix& a, double scalar)
{
    size_t rows = a.size();
    size_t cols = a[0].size();

    Matrix result(rows, std::vector<double>(cols, 0.0));

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            result[i][j] = a[i][j] * scalar;
        }
    }

    return result;
}

Core::Matrix Core::MatrixTransposition(const Matrix& a)
{
    size_t rows = a.size();
    size_t cols = a[0].size();

    Matrix result(cols, std::vector<double>(rows, 0.0));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = a[i][j];
        }
    }

    return result;
}

std::vector<double> Core::VectorAddition(const std::vector<double>& a, const std::vector<double>& b)
{
    size_t size = a.size();

    if (size != b.size()) throw std::invalid_argument("Vectors must be of the same size.");

    std::vector<double> result(size, 0.0);

    for (size_t i = 0; i < size; i++)
    {
        result[i] = a[i] + b[i];
    }

    return result;
}

std::vector<double> Core::VectorSubtraction(const std::vector<double>& a, const std::vector<double>& b)
{
    size_t size = a.size();

    if (size != b.size()) throw std::invalid_argument("Vectors must be of the same size.");

    std::vector<double> result(size, 0.0);

    for (size_t i = 0; i < size; i++)
    {
        result[i] = a[i] - b[i];
    }

    return result;
}

std::vector<double> Core::VectorHadamardProduct(const std::vector<double>& a, const std::vector<double>& b)
{
    size_t n = a.size();
    
    if (n != b.size()) throw std::invalid_argument("Vectors must have the same size for element-wise multiplication!");

    std::vector<double> result(n);

    for (size_t i = 0; i < n; i++)
    {
        result[i] = a[i] * b[i];
    }

    return result;
}


std::vector<double> Core::MatrixVectorProduct(const Matrix& matrix, const std::vector<double>& vector)
{
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    if (vector.size() != cols) throw std::invalid_argument("Matrix and vector dimensions must be compatible for multiplication!");

    std::vector<double> result(rows, 0.0);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

std::vector<double> Core::FlattenedOuterProduct(const std::vector<double>& a, const std::vector<double>& b)
{
    size_t rows = a.size();
    size_t cols = b.size();
    std::vector<double> result(rows * cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i * cols + j] = a[i] * b[j];
        }
    }

    return result;
}


Core::Matrix Core::VectorToMatrix(const std::vector<double>& vector, size_t rows, size_t cols)
{
    if (vector.size() != rows * cols) throw std::invalid_argument("The product of rows and cols must be equal to the size of the input vector!");

    Matrix result(rows, std::vector<double>(cols));

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            result[i][j] = vector[i * cols + j];
        }
    }

    return result;
}

Core::Matrix Core::OuterProduct(const std::vector<double>& a, const std::vector<double>& b)
{
    size_t rows = a.size();
    size_t cols = b.size();
    Matrix result(rows, std::vector<double>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = a[i] * b[j];
        }
    }

    return result;
}



