#pragma once

namespace Core
{
    typedef std::vector<std::vector<double>> Matrix;

    Matrix Addition(const Matrix &a, const Matrix &b);
    Matrix Subtraction(const Matrix &a, const Matrix &b);
    Matrix Multiplication(const Matrix &a, const Matrix &b);
    Matrix ScalarMultiplication(const Matrix &a, double scalar);
    Matrix Transpose(const Matrix &a);
}
