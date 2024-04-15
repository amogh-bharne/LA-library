#include <iostream>
#include <iomanip>
#include "../include/linear_algebra/eigen.hpp"
#include "../include/linear_algebra/matrix.hpp"


int main() {
    // Test case 1: Symmetric matrix
    linear_algebra::Matrix<double, 3, 3> mat1 = {
        {4, 1, 1},
        {1, 4, 1},
        {1, 1, 4}
    };

    auto [lambda1, eigenvector1] = linear_algebra::power_iteration(mat1);
    std::cout << "Test case 1:" << std::endl;
    std::cout << "Dominant eigenvalue: " << lambda1 << std::endl;
    std::cout << "Dominant eigenvector: " << eigenvector1 << std::endl << std::endl;

    // Test case 2: Non-symmetric matrix
    linear_algebra::Matrix<double, 3, 3> mat2 = {
        {3, 2, 1},
        {1, 4, 2},
        {2, 1, 5}
    };

    auto [lambda2, eigenvector2] = linear_algebra::power_iteration(mat2);
    std::cout << "Test case 2:" << std::endl;
    std::cout << "Dominant eigenvalue: " << lambda2 << std::endl;
    std::cout << "Dominant eigenvector: " << eigenvector2 << std::endl << std::endl;

    return 0;
}