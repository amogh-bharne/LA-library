#include "../include/linear_algebra/auto_differentiation.hpp"
#include <iostream>

int main() {
    using namespace linear_algebra;

    // Create ADVariable with value 2 and derivative 1
    ADVariable<double> x(2.0, 1.0);

    // Create ADVariable with value 3 and derivative 0
    ADVariable<double> y(3.0, 0.0);

    // Compute exp(x * y) with auto-differentiation
    ADVariable<double> z = exp(x * y);

    std::cout << "z = " << z.getValue() << std::endl;
    std::cout << "dz/dx = " << z.getDerivative() << std::endl;

    return 0;
}