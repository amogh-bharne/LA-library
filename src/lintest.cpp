#include <iostream>
#include "../include/linear_algebra/linear_equations.hpp"



int main() {
    using namespace linear_algebra;

    // Define the matrix A and vector b for the system of linear equations Ax = b
    Matrix<double, 3, 3> A({{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}});
    Vector<double, 3> b({8, -11, -3});

    // Solve the linear equations
    try {
        Vector<double, 3> solution = solve_linear_equations(A, b);

        // Display the solution
        std::cout << "Solution for x:\n";
        for (size_t i = 0; i < solution.size(); ++i) {
            std::cout << "x[" << i << "] = " << solution(i) << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

