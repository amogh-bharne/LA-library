#include <iostream>
#include "../include/linear_algebra/vector.hpp" // Include the Vector class header file

using namespace linear_algebra;
int main() {


        Vector<double, 3> v1({1.0, 2.0, 3.0});
        Vector<double, 3> v2({4.0, 5.0, 6.0});
        Vector<double, 3> v3({7.0, 8.0, 9.0});

        auto result = Vector<double, 3>::linearCombination(2.0, v1, -1.5, v2, 3.0, v3);
        std::cout << result << std::endl; 


    // // Test case for default constructor
    // Vector<double, 3> vec1;
    // std::cout << "Default constructed vector: " << vec1 << std::endl;

    // // Test case for constructor with array
    // double arr[3] = {1.0, 2.0, 3.0};
    // linear_algebra::Vector<double, 3> vec2(arr);
    // std::cout << "Vector constructed from array: " << vec2 << std::endl;

    // Vector<float,3> v2({2,3,4});

    // Vector<float,3> v3({2,3,4});

    // Vector<float,3> v1({2,3,4});



    // auto sum= Vector<float,3>::add(v1,v2,v3);

    // std::cout<<sum;


    // // Test case for addition
    // linear_algebra::Vector<double, 3> vec3 = vec1 + vec2;
    // std::cout << "Result of addition: " << vec3 << std::endl;

    // // Test case for subtraction
    // linear_algebra::Vector<double, 3> vec4 = vec2 - vec1;
    // std::cout << "Result of subtraction: " << vec4 << std::endl;

    // // Test case for scalar multiplication
    // linear_algebra::Vector<double, 3> vec5 = vec2 * 2.0;
    // std::cout << "Result of scalar multiplication: " << vec5 << std::endl;

    // // Test case for dot product
    // double dotProduct = vec2.dot(vec1);
    // std::cout << "Dot product: " << dotProduct << std::endl;

    // // Test case for cross product (only applicable for 3D vectors)
    // linear_algebra::Vector<double, 3> vec6 ({1.0, 2.0, 3.0});
    // linear_algebra::Vector<double, 3> vec7 ({4.0, 5.0, 6.0});
    // linear_algebra::Vector<double, 3> crossProduct = vec6.cross(vec7);
    // std::cout << "Cross product: " << crossProduct << std::endl;

    // // Test case for normalization
    // linear_algebra::Vector<double, 3> vec8 ({3.0, 4.0, 0.0});
    // linear_algebra::Vector<double, 3> normalizedVec8 = vec8.normalize();
    // std::cout << "Normalized vector: " << normalizedVec8 << std::endl;

    // // Test case for magnitude
    // double magnitude = vec8.magnitude();
    // std::cout << "Magnitude of vector: " << magnitude << std::endl;



    return 0;
}
