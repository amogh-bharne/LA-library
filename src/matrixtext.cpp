#include <iostream>
#include <iomanip>
#include "../include/linear_algebra/matrix.hpp"


using namespace linear_algebra;

int main() {
    // Test default constructor
    std::cout << "Testing default constructor:\n";
    Matrix<double, 3, 3> m1;
    m1.display();
    std::cout << std::endl;

    // Test array constructor
    std::cout << "Testing array constructor:\n";
    std::array<std::array<double, 2>, 2> data = {{{1.0, 2.0}, {3.0, 4.0}}};
    Matrix<double, 2, 2> m2(data);
    m2.display();
    std::cout << std::endl;

    // Test initializer list constructor
    std::cout << "Testing initializer list constructor:\n";
    Matrix<double, 2, 2> m3({{1.0, 2.0}, {3.0, 4.0}});
    m3.display();
    std::cout << std::endl;

    // Test accessor functions
    std::cout << "Testing accessor functions:\n";
    std::cout << "m2(0, 0) = " << m2(0, 0) << std::endl;
    m2(0, 0) = 5.0;
    std::cout << "m2(0, 0) = " << m2(0, 0) << std::endl;
    std::cout << std::endl;

    // Test addition
    std::cout << "Testing addition:\n";
    Matrix<double, 2, 2> m4{{1.0, 2.0}, {3.0, 4.0}};
    Matrix<double, 2, 2> m5{{5.0, 6.0}, {7.0, 8.0}};
    Matrix<double, 2, 2> m6 = m4 + m5;
    m6.display();
    std::cout << std::endl;

    // Test subtraction
    std::cout << "Testing subtraction:\n";
    Matrix<double, 2, 2> m7 = m5 - m4;
    m7.display();
    std::cout << std::endl;

    // Test multiplication
    std::cout << "Testing multiplication:\n";
    Matrix<double, 2, 3> m8{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    Matrix<double, 3, 2> m9{{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};
    Matrix<double, 2, 2> m10 = m8 * m9;
    m10.display();
    std::cout << std::endl;

    // Test matrix-vector multiplication
    std::cout << "Testing matrix-vector multiplication:\n";
    Vector<double, 3> v({7.0, 8.0, 9.0});
    Vector<double, 2> w = m8 * v;
    std::cout << "w = [" << w[0] << ", " << w[1] << "]" << std::endl;
    std::cout << std::endl;

    // Test scalar multiplication
    std::cout << "Testing scalar multiplication:\n";
    Matrix<double, 2, 2> m11 = m4 * 2.0;
    m11.display();
    std::cout << std::endl;

    // Test scalar division
    std::cout << "Testing scalar division:\n";
    Matrix<double, 2, 2> m12 = m11 / 2.0;
    m12.display();
    std::cout << std::endl;

    // Test transpose
    std::cout << "Testing transpose:\n";
    Matrix<double, 2, 3> m13{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    Matrix<double, 3, 2> m14 = m13.transpose();
    m14.display();
    std::cout << std::endl;

    // Test inverse
    std::cout << "Testing inverse:\n";
    Matrix<double, 2, 2> m15{{1.0, 2.0}, {3.0, 4.0}};
    Matrix<double, 2, 2> m16 = m15.inverse();
    m16.display();
    std::cout << std::endl;

    // Test determinant
    std::cout << "Testing determinant:\n";
    double det = m15.determinant();
    std::cout << "Determinant of m15: " << det << std::endl;
    std::cout << std::endl;

    // Test Frobenius norm
    std::cout << "Testing Frobenius norm:\n";
    double norm = m15.norm();
    std::cout << "Frobenius norm of m15: " << norm << std::endl;
    std::cout << std::endl;

    // Test solve linear equations
    std::cout << "Testing solve linear equations:\n";
    Matrix<double, 3, 3> m17{{2.0, 1.0, 1.0}, {1.0, 2.0, 1.0}, {1.0, 1.0, 2.0}};
    Vector<double, 3> b({7.0, 6.0, 6.0});
    Vector<double, 3> x = m17.solve_linear_equations(b);
    std::cout << "Solution: [" << x[0] << ", " << x[1] << ", " << x[2] << "]" << std::endl;

    return 0;
}