#include <iostream>
#include "../include/linear_algebra/vector.hpp" // Include the Vector class header file

using namespace linear_algebra;

int main() {
    // Constructor
    Vector<float, 3> v1({1.0f, 2.0f, 3.0f});
    Vector<float, 4> v2({1.0f, 2.0f, 3.0f, 4.0f});

    // Basic operations
    Vector<float, 3> v3 = v1 + v1;
    Vector<float, 3> v4 = v1 - v1;
    Vector<float, 3> v5 = v1 * 2.0f;

    // Dot product
    float dot_product = v1.dot(v3);

    Vector<float, 3> cro({2.3f,3.55f,2.5f});

    // Cross product
    Vector<float, 3> v6 = v1.cross(cro);

    // Normalization
    Vector<float, 4> v7 = v2.normalize();

    // Magnitude
    float magnitude = v2.magnitude();

    // Output
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3 (v1 + v1): " << v3 << std::endl;
    std::cout << "v4 (v1 - v1): " << v4 << std::endl;
    std::cout << "v5 (v1 * 2.0f): " << v5 << std::endl;
    std::cout << "Dot product (v1.v3): " << dot_product << std::endl;
    std::cout << "Cross product (v1 x v3): " << v6 << std::endl;
    std::cout << "Normalized v2: " << v7 << std::endl;
    std::cout << "Magnitude of v2: " << magnitude << std::endl;

    // Vector addition with add()
    Vector<float, 3> v8 = Vector<float, 3>::add(v1, v3, v5);
    std::cout << "v8 (v1 + v3 + v5): " << v8 << std::endl;

    // Linear combination
    Vector<float, 3> v9 = Vector<float, 3>::linearCombination(2.0f, v1, 3.0f, v3, 4.0f, v5);
    std::cout << "v9 (2*v1 + 3*v3 + 4*v5): " << v9 << std::endl;

    // Functional transformations
    Vector<float, 3> v10 = v1.transform([](float x) { return x * 99; });
    Vector<float, 3> v11 = v1.square();
    Vector<float, 3> v12 = v1.cube();

    std::cout << "v10 (v1 times 99): " << v10 << std::endl;
    std::cout << "v11 (v1 squared element-wise): " << v11 << std::endl;
    std::cout << "v12 (v1 cubed element-wise): " << v12 << std::endl;

    return 0;
}