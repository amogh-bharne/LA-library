// matrix.hpp

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <array>
#include <type_traits>
#include <cmath>
#include <stdexcept>
#include "vector.hpp"

namespace linear_algebra {

    // Forward declaration
    template<typename T, int Rows, int Cols>
    class Matrix;

    // Traits to check if a matrix is square
    template<typename T, int Rows, int Cols>
    struct is_square_matrix : std::false_type {};

    template<typename T, int N>
    struct is_square_matrix<Matrix<T, N, N>, N, N> : std::true_type {};

    // Concepts to check if T is a numeric type
    template <typename T>
    concept Numeric = std::is_arithmetic_v<T>;


    // Matrix class definition
    template<typename T, int Rows, int Cols>
    class Matrix {
    public:
        // Constructors
        Matrix();
        Matrix(const std::array<std::array<T, Cols>, Rows>& data);
        Matrix(const std::initializer_list<std::initializer_list<T>>& init_list);

        // Accessor and mutator functions
        T& operator()(int row, int col);
        const T& operator()(int row, int col) const;

        // Basic operations
        friend Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& a, const Matrix<T, Rows, Cols>& b) {
            Matrix<T, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result.data[i][j] = a.data[i][j] + b.data[i][j];
                }
            }
            return result;
        }

        friend Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& a, const Matrix<T, Rows, Cols>& b) {
            Matrix<T, Rows, Cols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    result.data[i][j] = a.data[i][j] - b.data[i][j];
                }
            }
            return result;
        }

        template<int OtherCols>
        friend Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Rows, Cols>& a, const Matrix<T, Cols, OtherCols>& b) {
            Matrix<T, Rows, OtherCols> result;
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < OtherCols; ++j) {
                    for (int k = 0; k < Cols; ++k) {
                        result.data[i][j] += a.data[i][k] * b.data[k][j];
                    }
                }
            }
            return result;
        }

        //Multiply vector and matrix
 
        template<size_t N>
        friend Vector<T, Rows> operator*(const Matrix<T,Rows,Cols>& mat ,const Vector<T, N>& vec) {
        static_assert(Cols == N, "Number of columns in the matrix must match the size of the vector.");
        Vector<T, Rows> result;
        for (size_t i = 0; i < Rows; ++i) {
            T sum = 0;
            for (size_t j = 0; j < Cols; ++j) {
                sum += mat.data[i][j] * vec[j];
            }
            result[i] = sum;
        }
        return result;
    }

        // Scalar operations
        Matrix<T, Rows, Cols> operator*(T scalar) const requires Numeric<T>;
        Matrix<T, Rows, Cols> operator/(T scalar) const requires Numeric<T>;

        // Transpose
        Matrix<T, Cols, Rows> transpose() const;

        // Inverse (if possible)
        Matrix<T, Rows, Cols> inverse() const requires Numeric<T>;

        // Determinant (if possible)
        double determinant() const requires Numeric<T>;

        // Display matrix
        void display() const;

        // Calculate the Frobenius norm of the matrix
        T norm() const requires Numeric<T>;

        //solve linear equations
        template<size_t N>
        Vector<T, N> solve_linear_equations(Vector<T, N>& b) requires Numeric<T> && is_square_matrix<Matrix<T, Rows, Cols>, Rows, Cols>::value {

            // Calculate the inverse of the coefficient matrix
            Matrix<T, N, N> A_inv = this->inverse();

            // Solve the system of linear equations
            Vector<T, N> x = A_inv * b;

            return x;
        }

        std::array<std::array<T, Cols>, Rows> data;
    };

    // Constructors
    template<typename T, int Rows, int Cols>
    Matrix<T, Rows, Cols>::Matrix() {
        // Initialize all elements to zero
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                data[i][j] = T();
            }
        }
    }

    template<typename T, int Rows, int Cols>
    Matrix<T, Rows, Cols>::Matrix(const std::array<std::array<T, Cols>, Rows>& data) : data(data) {}

    template<typename T, int Rows, int Cols>
    Matrix<T, Rows, Cols>::Matrix(const std::initializer_list<std::initializer_list<T>>& init_list) {
        if (init_list.size() != Rows) {
            throw std::invalid_argument("Invalid number of rows in initializer list");
        }
        int row_index = 0;
        for (const auto& row : init_list) {
            if (row.size() != Cols) {
                throw std::invalid_argument("Invalid number of columns in initializer list");
            }
            int col_index = 0;
            for (const auto& elem : row) {
                data[row_index][col_index++] = elem;
            }
            ++row_index;
        }
    }

    // Accessor and mutator functions
    template<typename T, int Rows, int Cols>
    T& Matrix<T, Rows, Cols>::operator()(int row, int col) {
        return data[row][col];
    }

    template<typename T, int Rows, int Cols>
    const T& Matrix<T, Rows, Cols>::operator()(int row, int col) const {
        return data[row][col];
    }

    // Scalar operations
    template<typename T, int Rows, int Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator*(T scalar) const requires Numeric<T> {
        Matrix<T, Rows, Cols> result;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    template<typename T, int Rows, int Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator/(T scalar) const requires Numeric<T> {
        if (scalar == 0) {
            throw std::runtime_error("Division by zero");
        }
        Matrix<T, Rows, Cols> result;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    // Transpose
    template<typename T, int Rows, int Cols>
    Matrix<T, Cols, Rows> Matrix<T, Rows, Cols>::transpose() const {
        Matrix<T, Cols, Rows> result;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // Inverse (if possible)
    template<typename T, int Rows, int Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::inverse() const requires Numeric<T> {
        static_assert(is_square_matrix<Matrix<T, Rows, Cols>, Rows, Cols>::value, "Inverse is only defined for square matrices");

        // Calculate the determinant of the matrix
        T det = determinant();
        if (det == T(0)) {
            // Matrix is singular, inverse doesn't exist
            throw std::runtime_error("Matrix is singular, inverse doesn't exist");
        }

        // Calculate the adjugate matrix
        Matrix<T, Rows, Cols> adjugate;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                // Calculate the cofactor of element (i, j)
                Matrix<T, Rows - 1, Cols - 1> minor;
                for (int m = 0, p = 0; m < Rows; ++m) {
                    if (m == i) continue;
                    for (int n = 0, q = 0; n < Cols; ++n) {
                        if (n == j) continue;
                        minor(p, q++) = data[m][n];
                    }
                    ++p;
                }
                // Calculate the sign of the cofactor
                T sign = ((i + j) % 2 == 0) ? T(1) : T(-1);
                // Calculate the determinant of the minor matrix
                T minor_det = minor.determinant();
                // Calculate the cofactor
                adjugate(j, i) = sign * minor_det;
            }
        }

        // Divide the adjugate matrix by the determinant
        Matrix<T, Rows, Cols> inversed;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                inversed(i, j) = adjugate(i, j) / det;
            }
        }

        return inversed;
    }

    // Calculate the Frobenius norm of the matrix
    template<typename T, int Rows, int Cols>
    T Matrix<T, Rows, Cols>::norm() const requires Numeric<T> {
        T sum = T();
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                sum += data[i][j] * data[i][j];
            }
        }
        return std::sqrt(sum);
    }

    // Display matrix
    template<typename T, int Rows, int Cols>
    void Matrix<T, Rows, Cols>::display() const {
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    template<typename T, int Rows, int Cols>
    double determinant_helper(const Matrix<T, Rows, Cols>& mat, const int n) requires Numeric<T> {
        double det = 0;
        if (n == 1) {
            return mat(0, 0); // For a 1x1 matrix, determinant is the single element
        } else if (n == 2) {
            return mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0); // For a 2x2 matrix, use the standard formula
        } else {
            Matrix<T, Rows, Cols> submat;
            for (int x = 0; x < n; x++) {
                int subi = 0;
                for (int i = 1; i < n; i++) {
                    int subj = 0;
                    for (int j = 0; j < n; j++) {
                        if (j == x)
                            continue;
                        submat(subi, subj) = mat(i, j);
                        subj++;
                    }
                    subi++;
                }
                det += (pow(-1, x) * mat(0, x) * determinant_helper(submat, n - 1));
            }
        }
        return det;
    }

    // Determinant (if possible)
    template<typename T, int Rows, int Cols>
    double Matrix<T, Rows, Cols>::determinant() const requires Numeric<T> {
        static_assert(is_square_matrix<Matrix<T, Rows, Cols>, Rows, Cols>::value, "Determinant is only defined for square matrices");
        return determinant_helper(*this, Rows);
    }

} // namespace linear_algebra

#endif // MATRIX_HPP