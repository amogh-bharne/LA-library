// main.cpp

#include <iostream>
#include "../include/linear_algebra/vector.hpp"

using namespace linear_algebra;

// Example usage of the Vector class
int main() {
    // Example usage of the Vector class
    Vector<double, 3> v1({1.0, 2.0, 3.0});
    Vector<double, 3> v2({4.0, 5.0, 6.0});

    // Addition
    Vector<double, 3> sum = v1 + v2;
    std::cout << "Sum: " << sum << std::endl;

    // Subtraction
    Vector<double, 3> diff = v1 - v2;
    std::cout << "Difference: " << diff << std::endl;

    // Scalar multiplication
    double scalar = 2.0;
    Vector<double, 3> scaled = v1 * scalar;
    std::cout << "Scaled: " << scaled << std::endl;

    // Dot product
    double dot_product = v1.dot(v2);
    std::cout << "Dot product: " << dot_product << std::endl;

    // Cross product (only for 3D vectors)
    Vector<double, 3> cross_product = v1.cross(v2);
    std::cout << "Cross product: " << cross_product << std::endl;

    // Normalization
    Vector<double, 3> normalized = v1.normalize();
    std::cout << "Normalized: " << normalized << std::endl;

    // Magnitude
    double magnitude = v1.magnitude();
    std::cout << "Magnitude: " << magnitude << std::endl;

    return 0;
}
