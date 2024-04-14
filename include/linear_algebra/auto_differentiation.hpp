// auto_differentiation.hpp

#ifndef AUTO_DIFFERENTIATION_HPP
#define AUTO_DIFFERENTIATION_HPP

#include "vector.hpp"
#include <cmath>

namespace linear_algebra {

    // Forward declaration for ADVariable
    template<typename T>
    class ADVariable;

    // Template specialization for constant ADVariable
    template<typename T>
    class ADVariable<T> {
    public:
        ADVariable(const T& value) : value(value), derivative(0) {}

        // Getter for value
        T getValue() const { return value; }

        // Getter for derivative
        T getDerivative() const { return derivative; }

    private:
        T value;
        T derivative;
    };

    // Template specialization for ADVariable with derivative
    template<typename T>
    class ADVariable<ADVariable<T>> {
    public:
        ADVariable(const T& value, const T& derivative) : value(value), derivative(derivative) {}

        // Getter for value
        T getValue() const { return value.getValue(); }

        // Getter for derivative
        T getDerivative() const { return derivative; }

    private:
        ADVariable<T> value;
        T derivative;
    };

    // Overloaded arithmetic operations for ADVariable
    template<typename T>
    ADVariable<T> operator+(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() + rhs.getValue(), lhs.getDerivative() + rhs.getDerivative());
    }

    template<typename T>
    ADVariable<T> operator-(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() - rhs.getValue(), lhs.getDerivative() - rhs.getDerivative());
    }

    template<typename T>
    ADVariable<T> operator*(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() * rhs.getValue(), lhs.getValue() * rhs.getDerivative() + lhs.getDerivative() * rhs.getValue());
    }

    template<typename T>
    ADVariable<T> operator/(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() / rhs.getValue(), (lhs.getDerivative() * rhs.getValue() - lhs.getValue() * rhs.getDerivative()) / (rhs.getValue() * rhs.getValue()));
    }

    // Elementary functions with auto-differentiation support
    template<typename T>
    ADVariable<T> exp(const ADVariable<T>& x) {
        return ADVariable<T>(std::exp(x.getValue()), x.getDerivative() * std::exp(x.getValue()));
    }

    template<typename T>
    ADVariable<T> log(const ADVariable<T>& x) {
        return ADVariable<T>(std::log(x.getValue()), x.getDerivative() / x.getValue());
    }

    template<typename T>
    ADVariable<T> sin(const ADVariable<T>& x) {
        return ADVariable<T>(std::sin(x.getValue()), x.getDerivative() * std::cos(x.getValue()));
    }

    template<typename T>
    ADVariable<T> cos(const ADVariable<T>& x) {
        return ADVariable<T>(std::cos(x.getValue()), -x.getDerivative() * std::sin(x.getValue()));
    }

    // Example usage:
    // ADVariable<double> x(2, 1); // Create ADVariable with value 2 and derivative 1
    // ADVariable<double> y(3, 0); // Create ADVariable with value 3 and derivative 0
    // ADVariable<double> z = exp(x * y); // Compute exp(x * y) with auto-differentiation

} // namespace linear_algebra

#endif // AUTO_DIFFERENTIATION_HPP
