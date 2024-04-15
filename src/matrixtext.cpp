#include "../include/linear_algebra/matrix.hpp"

#include <iostream>

int main() {
    // Creating matrices for testing
    //linear_algebra::Matrix<double, 2, 2> mat2x2({{1, 2}, {3, 4}});
    linear_algebra::Matrix<double, 3, 3> mat3x2({{9,6,3},{0,6,7},{0,0,9}});
    //linear_algebra::Matrix<double, 4, 4> mat4x4({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});

    // Displaying original matrices
    //std::cout << "Original 2x2 Matrix:" << std::endl;
    //mat2x2.display();

    std::cout << "\nOriginal 3x2 Matrix:" << std::endl;
    mat3x2.display();

    //std::cout << "\nOriginal 4x4 Matrix:" << std::endl;
    //mat4x4.display();

    // //Testing transpose
    // std::cout << "\nTransposed 2x2 Matrix:" << std::endl;
    // mat2x2.transpose().display();

    // std::cout << "\nTransposed 3x3 Matrix:" << std::endl;
    // mat3x3.transpose().display();

    // std::cout << "\nTransposed 4x4 Matrix:" << std::endl;
    // mat4x4.transpose().display();

    // Testing determinant
    //std::cout << "\nDeterminant of 2x2 Matrix: " << mat2x2.determinant() << std::endl;
    //std::cout << "Determinant of 3x3 Matrix: " << mat3x3.determinant() << std::endl;
    //std::cout << "Determinant of 4x4 Matrix: " << mat4x4.determinant() << std::endl;

    // // Testing Frobenius norm
    // std::cout << "\nFrobenius Norm of 2x2 Matrix: " << mat2x2.norm() << std::endl;
    // std::cout << "Frobenius Norm of 3x3 Matrix: " << mat3x3.norm() << std::endl;
    // std::cout << "Frobenius Norm of 4x4 Matrix: " << mat4x4.norm() << std::endl;

    // // Testing scalar operations
    // double scalar = 2.5;
    // std::cout << "\n2x2 Matrix after multiplying with scalar " << scalar << ":" << std::endl;
    // (mat2x2 * scalar).display();

    // std::cout << "\n3x3 Matrix after dividing by scalar " << scalar << ":" << std::endl;
    // (mat3x3 / scalar).display();

    // // Testing matrix operations
    // std::cout << "\nSum of 3x3 and 3x3 matrices:" << std::endl;
    // (mat3x3 + mat3x3).display();

    // std::cout << "\nDifference of 3x3 and 3x3 matrices:" << std::endl;
    // (mat3x3 - mat3x3).display();

    // std::cout << "\nProduct of 3x3 and 3x3 matrices:" << std::endl;
    // (mat3x3 * mat3x3).display();

    // Testing inverse
    // try {
    //     std::cout << "\nInverse of 2x2 Matrix:" << std::endl;
    //     mat2x2.inverse().display();
    // } catch (const std::exception& e) {
    //     std::cerr << "Exception while computing inverse: " << e.what() << std::endl;
    // }

    // try {
    //     std::cout << "\nInverse of 3x3 Matrix:" << std::endl;
    //     mat3x3.inverse().display();
    // } catch (const std::exception& e) {
    //     std::cerr << "Exception while computing inverse: " << e.what() << std::endl;
    // }

    // try {
    //     std::cout << "\nInverse of 4x4 Matrix:" << std::endl;
    //     mat4x4.inverse().display();
    // } catch (const std::exception& e) {
    //     std::cerr << "Exception while computing inverse: " << e.what() << std::endl;
    // }

    //testing eigen

    //auto [eigenvalues, eigenvectors] = mat3x2.eigen();
    //std::cout << "\nEigenvalues of 3x3 Matrix:" << std::endl;
    

    return 0;
}
