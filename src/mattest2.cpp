#include "../include/linear_algebra/matrix.hpp"

#include <iostream>

using namespace linear_algebra;

int main()
{
    Matrix<int,3,3> mat({{1,2,3},{4,5,6},{7,8,9}});
    Vector<int,3> vec({1,2,3});

    //multiply

    Vector<int,3> res;

    res=mat*vec;

    std::cout<<res;

        Matrix<double, 3, 3> A ({
        {2, 3, -1},
        {1, -1, 2},
        {-1, 2, 1}
    });

    // Construct the right-hand side vector
    Vector<double, 3> b ({5, 8, 3});

    // Solve the system of linear equations
    Vector<double, 3> x = A.solve_linear_equations(b);

    // Print the solution
    std::cout << "Solution:" << std::endl;
    std::cout << "x = " << x[0] << std::endl;
    std::cout << "y = " << x[1] << std::endl;
    std::cout << "z = " << x[2] << std::endl;

    return 0;

}