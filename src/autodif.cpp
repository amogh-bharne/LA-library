#include "../include/linear_algebra/auto_differentiation.hpp"
#include <iostream>

int main() {
    using namespace linear_algebra;

    ADVariable<double> x(2.0, 1.0);
    ADVariable<double> y(3.0, 0.0);
    ADVariable<double> z(4.0, 0.5);

    // Use the sum function with variadic templates
    ADVariable<double> sum_of_vars = sum(x, y, z);
    std::cout << "Sum of variables: " << sum_of_vars.getValue() << ", Derivative: " << sum_of_vars.getDerivative() << std::endl;

    // Use the transform function with a lambda template
    auto square = [](double v) { return v * v; };
    ADVariable<double> squared_x = transform(x, square);
    std::cout << "Squared x: " << squared_x.getValue() << ", Derivative: " << squared_x.getDerivative() << std::endl;

    return 0;
}