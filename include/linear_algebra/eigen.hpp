// eigen.hpp

#ifndef EIGEN_HPP
#define EIGEN_HPP

#include "matrix.hpp"
#include <cmath>
#include <utility>

namespace linear_algebra {

    // Power iteration method to find the dominant eigenvalue and eigenvector
    template<typename T, size_t Rows, size_t Cols>
    std::pair<T, Matrix<T, Rows, 1>> power_iteration(const Matrix<T, Rows, Cols>& mat, size_t max_iterations = 1000, T tolerance = 1e-6) {
        // Initialize a random vector as the initial guess
        Matrix<T, Rows, 1> eigenvector;
        for (size_t i = 0; i < Rows; ++i) {
            eigenvector(i, 0) = static_cast<T>(rand()) / RAND_MAX;
        }

        T lambda_prev = 0;
        T lambda = 0;
        for (size_t iter = 0; iter < max_iterations; ++iter) {
            // Multiply matrix by the eigenvector
            Matrix<T, Rows, 1> product = mat * eigenvector;
            // Find the norm of the product
            T norm = product.norm();
            // Normalize the eigenvector
            eigenvector = product / norm;
            // Calculate the eigenvalue
            lambda = (eigenvector.transpose() * mat * eigenvector)(0, 0);
            // Check for convergence
            if (std::abs(lambda - lambda_prev) < tolerance) {
                break;
            }
            lambda_prev = lambda;
        }

        return {lambda, eigenvector};
    }

} // namespace linear_algebra

#endif // EIGEN_HPP
