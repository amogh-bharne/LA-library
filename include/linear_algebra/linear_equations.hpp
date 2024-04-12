// linear_equations.hpp

#ifndef LINEAR_EQUATIONS_HPP
#define LINEAR_EQUATIONS_HPP

#include "matrix.hpp"
#include "vector.hpp"
#include <stdexcept>
#include <concepts>

namespace linear_algebra {

    // Concept for matrix and vector types supporting basic arithmetic operations and element access
    template<typename M, typename V>
    concept LinearAlgebraSupport = requires(M m, V v) {
        { m(0, 0) } -> std::convertible_to<typename M::value_type>;
        { v[0] } -> std::convertible_to<typename V::value_type>;
        { m * v };
    };

    // Function to solve linear equations Ax = b using Gauss elimination method
    template<typename T, size_t Size, typename MatrixType, typename VectorType>
    requires LinearAlgebraSupport<MatrixType, VectorType>
    Vector<T, Size> solve_linear_equations(const MatrixType& A, const VectorType& b) {
        static_assert(is_square_matrix<MatrixType, Size, Size>::value, "Matrix A must be square");

        // Augment matrix A with vector b
        Matrix<T, Size, Size + 1> augmented_matrix;
        for (size_t i = 0; i < Size; ++i) {
            for (size_t j = 0; j < Size; ++j) {
                augmented_matrix(i, j) = A(i, j);
            }
            augmented_matrix(i, Size) = b[i];
        }

        // Perform Gauss elimination
        for (size_t i = 0; i < Size; ++i) {
            // Pivot for this column
            size_t pivot_row = i;
            for (size_t j = i + 1; j < Size; ++j) {
                if (std::abs(augmented_matrix(j, i)) > std::abs(augmented_matrix(pivot_row, i))) {
                    pivot_row = j;
                }
            }
            if (augmented_matrix(pivot_row, i) == T(0)) {
                throw std::runtime_error("Matrix is singular, cannot solve linear equations");
            }
            if (pivot_row != i) {
                // Swap rows to make the pivot the largest element in this column
                for (size_t j = i; j < Size + 1; ++j) {
                    std::swap(augmented_matrix(i, j), augmented_matrix(pivot_row, j));
                }
            }
            // Eliminate all entries below the pivot
            for (size_t j = i + 1; j < Size; ++j) {
                T factor = augmented_matrix(j, i) / augmented_matrix(i, i);
                for (size_t k = i; k < Size + 1; ++k) {
                    augmented_matrix(j, k) -= factor * augmented_matrix(i, k);
                }
            }
        }

        // Back substitution to find the solution
        Vector<T, Size> solution;
        for (int i = Size - 1; i >= 0; --i) {
            T sum = 0;
            for (size_t j = i + 1; j < Size; ++j) {
                sum += augmented_matrix(i, j) * solution[j];
            }
            solution[i] = (augmented_matrix(i, Size) - sum) / augmented_matrix(i, i);
        }

        return solution;
    }

} // namespace linear_algebra

#endif // LINEAR_EQUATIONS_HPP
