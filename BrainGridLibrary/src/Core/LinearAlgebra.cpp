#include "bgpch.h"
#include "LinearAlgebra.h"

Core::Matrix Core::Addition(const Matrix& a, const Matrix& b)
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

Core::Matrix Core::Subtraction(const Matrix& a, const Matrix& b)
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

Core::Matrix Core::Multiplication(const Matrix& a, const Matrix& b)
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

Core::Matrix Core::ScalarMultiplication(const Matrix& a, double scalar)
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

Core::Matrix Core::Transpose(const Matrix& a)
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

