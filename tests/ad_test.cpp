#include <iostream>
#include "../include/linear_algebra/auto_differentiation.hpp"

using namespace std;
using namespace linear_algebra;

int main() {
    // Test case 1: Basic arithmetic operations
    ADVariable<double> a(2.0, 1.0); // x = 2, dx/dx = 1
    ADVariable<double> b(3.0, 1.0); // y = 3, dy/dy = 1
    ADVariable<double> c = a + b;   // c = x + y = 5, dc/dx = dc/dy = 1
    cout << "Test case 1: a + b = " << c.getValue() << ", dc/da = dc/db = " << c.getDerivative() << endl;

    // Test case 2: Elementary functions
    ADVariable<double> x(1.0, 1.0); // x = 1, dx/dx = 1
    ADVariable<double> y = exp(x);   // y = exp(x) = e^1, dy/dx = e^1
    cout << "Test case 2: exp(1) = " << y.getValue() << ", dy/dx = " << y.getDerivative() << endl;

    // Test case 3: Composite functions
    ADVariable<double> z = sin(x * x); // z = sin(x^2), dz/dx = 2x * cos(x^2)
    cout << "Test case 3: sin(x^2) = " << z.getValue() << ", dz/dx at x=1: " << transform(z, [](double val) { return val; }).getDerivative() << endl;

    // Test case 4: Variadic sum function
    ADVariable<double> d(4.0, 1.0); // z = 4, dz/dz = 1
    ADVariable<double> e(5.0, 1.0); // w = 5, dw/dw = 1
    ADVariable<double> f = sum(a, b, c, d, e); // f = x + y + z + w + z = 2 + 3 + 5 + 4 + 5 = 19
    cout << "Test case 4: sum(a, b, c, d, e) = " << f.getValue() << ", df/da = df/db = df/dc = df/dd = df/de = " << f.getDerivative() << endl;

    return 0;
}
