// pca.hpp

#ifndef PCA_HPP
#define PCA_HPP

#include "matrix.hpp"
#include "vector.hpp"
#include "eigen.hpp"
#include <cmath>

namespace linear_algebra {

    // Function to perform Principal Component Analysis (PCA)
    template<typename T, size_t Rows, size_t Cols>
    std::pair<Matrix<T, Cols, Cols>, Matrix<T, Rows, Cols>> pca(const Matrix<T, Rows, Cols>& data) {
        // Calculate the mean vector
        Vector<T, Cols> mean_vector = data.mean();

        // Center the data by subtracting the mean
        Matrix<T, Rows, Cols> centered_data = data;
        for (size_t i = 0; i < Rows; ++i) {
            centered_data.row(i) -= mean_vector;
        }

        // Calculate the covariance matrix
        Matrix<T, Cols, Cols> covariance_matrix = (centered_data.transpose() * centered_data) / static_cast<T>(Rows - 1);

        // Perform eigenvalue decomposition to find principal components
        auto [eigenvalues, eigenvectors] = eigen(covariance_matrix);

        // Sort eigenvalues and eigenvectors in descending order
        auto eigen_sort_indices = eigenvalues.argsort_descending();
        eigenvalues = eigenvalues[eigen_sort_indices];
        eigenvectors = eigenvectors.columnwise()[eigen_sort_indices];

        return {eigenvalues, eigenvectors};
    }

} // namespace linear_algebra

#endif // PCA_HPP
