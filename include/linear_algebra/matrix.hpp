// matrix.hpp

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <array>
#include <type_traits>
#include <cmath>
#include <stdexcept>

namespace linear_algebra {

    // Forward declaration
    template<typename T, size_t Rows, size_t Cols>
    class Matrix;

    // Traits to check if a matrix is square
    template<typename T, size_t Rows, size_t Cols>
    struct is_square_matrix : std::false_type {};

    template<typename T, size_t N>
    struct is_square_matrix<Matrix<T, N, N>, N, N> : std::true_type {};

    // Forward declaration for inverse
    template<typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> inverse(const Matrix<T, Rows, Cols>& mat);

    // Forward declaration for determinant
    template<typename T, size_t Rows, size_t Cols>
    T determinant(const Matrix<T, Rows, Cols>& mat);

    // Matrix class definition
    template<typename T, size_t Rows, size_t Cols>
    class Matrix {
    public:
        // Constructors
        Matrix();
        Matrix(const std::array<std::array<T, Cols>, Rows>& data);

        // Accessor and mutator functions
        T& operator()(size_t row, size_t col);
        const T& operator()(size_t row, size_t col) const;

        // Basic operations
        friend Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& a, const Matrix<T, Rows, Cols>& b) {
            Matrix<T, Rows, Cols> result;
            for (size_t i = 0; i < Rows; ++i) {
                for (size_t j = 0; j < Cols; ++j) {
                    result.data[i][j] = a.data[i][j] + b.data[i][j];
                }
            }
            return result;
        }

        friend Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& a, const Matrix<T, Rows, Cols>& b) {
            Matrix<T, Rows, Cols> result;
            for (size_t i = 0; i < Rows; ++i) {
                for (size_t j = 0; j < Cols; ++j) {
                    result.data[i][j] = a.data[i][j] - b.data[i][j];
                }
            }
            return result;
        }

        template<size_t OtherCols>
        friend Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Rows, Cols>& a, const Matrix<T, Cols, OtherCols>& b) {
            Matrix<T, Rows, OtherCols> result;
            for (size_t i = 0; i < Rows; ++i) {
                for (size_t j = 0; j < OtherCols; ++j) {
                    for (size_t k = 0; k < Cols; ++k) {
                        result.data[i][j] += a.data[i][k] * b.data[k][j];
                    }
                }
            }
            return result;
        }

        // Scalar operations
        Matrix<T, Rows, Cols> operator*(T scalar) const;
        Matrix<T, Rows, Cols> operator/(T scalar) const;

        // Transpose
        Matrix<T, Cols, Rows> transpose() const;

        // Inverse (if possible)
        Matrix<T, Rows, Cols> inverse() const;

        // Determinant (if possible)
        T determinant() const;

        // Display matrix
        void display() const;

    private:
        std::array<std::array<T, Cols>, Rows> data;
    };

    // Constructors
    template<typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols>::Matrix() {
        // Initialize all elements to zero
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                data[i][j] = T();
            }
        }
    }

    template<typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols>::Matrix(const std::array<std::array<T, Cols>, Rows>& data) : data(data) {}

    // Accessor and mutator functions
    template<typename T, size_t Rows, size_t Cols>
    T& Matrix<T, Rows, Cols>::operator()(size_t row, size_t col) {
        return data[row][col];
    }

    template<typename T, size_t Rows, size_t Cols>
    const T& Matrix<T, Rows, Cols>::operator()(size_t row, size_t col) const {
        return data[row][col];
    }

    // Scalar operations
    template<typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator*(T scalar) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    template<typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator/(T scalar) const {
        if (scalar == 0) {
            throw std::runtime_error("Division by zero");
        }
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    // Transpose
    template<typename T, size_t Rows, size_t Cols>
    Matrix<T, Cols, Rows> Matrix<T, Rows, Cols>::transpose() const {
        Matrix<T, Cols, Rows> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // Implementation of inverse function (adjugate method)
    template<typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::inverse() const {
        static_assert(is_square_matrix<Matrix<T, Rows, Cols>, Rows, Cols>::value, "Inverse is only defined for square matrices");

        // Calculate the determinant of the matrix
        T det = determinant();
        if (det == T(0)) {
            // Matrix is singular, inverse doesn't exist
            throw std::runtime_error("Matrix is singular, inverse doesn't exist");
        }

        // Calculate the adjugate matrix
        Matrix<T, Rows, Cols> adjugate;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                // Calculate the cofactor of element (i, j)
                Matrix<T, Rows - 1, Cols - 1> minor;
                for (size_t m = 0, p = 0; m < Rows; ++m) {
                    if (m == i) continue;
                    for (size_t n = 0, q = 0; n < Cols; ++n) {
                        if (n == j) continue;
                        minor(p, q++) = data[m][n];
                    }
                    ++p;
                }
                // Calculate the sign of the cofactor
                T sign = ((i + j) % 2 == 0) ? T(1) : T(-1);
                // Calculate the determinant of the minor matrix
                T minor_det = determinant(minor);
                // Calculate the cofactor
                adjugate(j, i) = sign * minor_det;
            }
        }

        // Divide the adjugate matrix by the determinant
        Matrix<T, Rows, Cols> inversed;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                inversed(i, j) = adjugate(i, j) / det;
            }
        }

        return inversed;
    }

    // Determinant (if possible)
    template<typename T, size_t Rows, size_t Cols>
    T Matrix<T, Rows, Cols>::determinant() const {
        return determinant(*this);
    }

    // Display matrix
    template<typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::display() const {
        auto print_row = [](const auto& row) {
            ((std::cout << row << "\t"), ...);
            std::cout << std::endl;
        };
        for (const auto& row : data) {
            print_row(row);
        }
    }

    // Helper function to calculate determinant of square matrix
    template<typename T, size_t Rows, size_t Cols>
    T determinant(const Matrix<T, Rows, Cols>& mat) {
        static_assert(is_square_matrix<Matrix<T, Rows, Cols>, Rows, Cols>::value, "Determinant is only defined for square matrices");

        if constexpr (Rows == 1 && Cols == 1) {
            return mat(0, 0);
        } else if constexpr (Rows == 2 && Cols == 2) {
            return mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);
        } else {
            T det = 0;
            for (size_t j = 0; j < Cols; ++j) {
                T sign = (j % 2 == 0) ? T(1) : T(-1);
                Matrix<T, Rows - 1, Cols - 1> minor;
                for (size_t i = 1; i < Rows; ++i) {
                    for (size_t k = 0, l = 0; k < Cols; ++k) {
                        if (k == j) continue;
                        minor(i - 1, l++) = mat(i, k);
                    }
                }
                det += sign * mat(0, j) * determinant(minor);
            }
            return det;
        }
    }

} // namespace linear_algebra

#endif // MATRIX_HPP
