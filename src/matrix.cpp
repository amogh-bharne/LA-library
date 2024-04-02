#include "matrix.hpp"

namespace linear_algebra {

    // Implementation of methods for Matrix class goes here

    // Default constructor
    template<typename T, size_t rows, size_t cols>
    Matrix<T, rows, cols>::Matrix() : data{} {}

    // Constructor with a single value
    template<typename T, size_t rows, size_t cols>
    Matrix<T, rows, cols>::Matrix(const T& value) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = value;
            }
        }
    }

    // Constructor with initializer list
    template<typename T, size_t rows, size_t cols>
    Matrix<T, rows, cols>::Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
        size_t i = 0, j = 0;
        for (const auto& row : list) {
            for (const auto& val : row) {
                if (i >= rows || j >= cols) break;
                data[i][j++] = val;
            }
            j = 0;
            ++i;
        }
    }

    // Constructor with variadic arguments
    template<typename T, size_t rows, size_t cols>
    template<typename... Args,
             typename>
    Matrix<T, rows, cols>::Matrix(Args... args) {
        static_assert(sizeof...(args) == rows * cols, "Number of arguments must match the size of the matrix");
        size_t i = 0, j = 0;
        ((data[i][j++] = args), ...);
    }

    // Copy constructor
    template<typename T, size_t rows, size_t cols>
    Matrix<T, rows, cols>::Matrix(const Matrix& other) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Destructor
    template<typename T, size_t rows, size_t cols>
    Matrix<T, rows, cols>::~Matrix() {}

    // Assignment operator
    template<typename T, size_t rows, size_t cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator=(const Matrix& other) {
        if (this != &other) {
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    // Access operator
    template<typename T, size_t rows, size_t cols>
    T& Matrix<T, rows, cols>::operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        return data[row][col];
    }

    // Const access operator
    template<typename T, size_t rows, size_t cols>
    const T& Matrix<T, rows, cols>::operator()(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        return data[row][col];
    }

    // Rows method
    template<typename T, size_t rows, size_t cols>
    size_t Matrix<T, rows, cols>::Rows() const {
        return rows;
    }

    // Cols method
    template<typename T, size_t rows, size_t cols>
    size_t Matrix<T, rows, cols>::Cols() const {
        return cols;
    }

    // Print method
    template<typename T, size_t rows, size_t cols>
    void Matrix<T, rows, cols>::Print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Scalar multiplication operator
    template<typename T, size_t rows, size_t cols, typename U>
    Matrix<T, rows, cols> operator*(const U& scalar, const Matrix<T, rows, cols>& mat) {
        Matrix<T, rows, cols> result;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = scalar * mat(i, j);
            }
        }
        return result;
    }

    // Explicit instantiations for common types
    template class Matrix<int, 2, 2>;
    template class Matrix<float, 2, 2>;
    template class Matrix<double, 2, 2>;

} // namespace linear_algebra
