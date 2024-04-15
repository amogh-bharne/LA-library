#ifndef AUTO_DIFFERENTIATION_HPP
#define AUTO_DIFFERENTIATION_HPP

#include <cmath>
#include <functional>

namespace linear_algebra {
    // Primary template for ADVariable
    template <typename T>
    class ADVariable {
    public:
        ADVariable(const T& value, const T& derivative)
            : value(value), derivative(derivative) {}

        T getValue() const { return value; }
        T getDerivative() const { return derivative; }

    private:
        T value;
        T derivative;
    };

    // Specialization for constant ADVariable
    template <typename T>
    class ADVariable<T*> {
    public:
        ADVariable(const T& value) : value(value), derivative(0) {}

        T getValue() const { return value; }
        T getDerivative() const { return derivative; }

    private:
        T value;
        T derivative;
    };

    // Overloaded arithmetic operations for ADVariable
    template <typename T>
    ADVariable<T> operator+(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() + rhs.getValue(), lhs.getDerivative() + rhs.getDerivative());
    }

    template <typename T>
    ADVariable<T> operator-(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() - rhs.getValue(), lhs.getDerivative() - rhs.getDerivative());
    }

    template <typename T>
    ADVariable<T> operator*(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() * rhs.getValue(), lhs.getValue() * rhs.getDerivative() + lhs.getDerivative() * rhs.getValue());
    }

    template <typename T>
    ADVariable<T> operator/(const ADVariable<T>& lhs, const ADVariable<T>& rhs) {
        return ADVariable<T>(lhs.getValue() / rhs.getValue(), (lhs.getDerivative() * rhs.getValue() - lhs.getValue() * rhs.getDerivative()) / (rhs.getValue() * rhs.getValue()));
    }

    // Elementary functions with auto-differentiation support
    template <typename T>
    ADVariable<T> exp(const ADVariable<T>& x) {
        return ADVariable<T>(std::exp(x.getValue()), x.getDerivative() * std::exp(x.getValue()));
    }

    template <typename T>
    ADVariable<T> log(const ADVariable<T>& x) {
        return ADVariable<T>(std::log(x.getValue()), x.getDerivative() / x.getValue());
    }

    template <typename T>
    ADVariable<T> sin(const ADVariable<T>& x) {
        return ADVariable<T>(std::sin(x.getValue()), x.getDerivative() * std::cos(x.getValue()));
    }

    template <typename T>
    ADVariable<T> cos(const ADVariable<T>& x) {
        return ADVariable<T>(std::cos(x.getValue()), -x.getDerivative() * std::sin(x.getValue()));
    }

    // Variadic template function for sum of ADVariable objects
    template <typename T, typename... Args>
    ADVariable<T> sum(const ADVariable<T>& first, const Args&... rest) {
        return (first + ... + ADVariable<T>(rest.getValue(), rest.getDerivative()));
    }

    // Lambda template for generic transformation of ADVariable objects
    template <typename T, typename Func>
    ADVariable<T> transform(const ADVariable<T>& x, Func&& f) {
        return ADVariable<T>(f(x.getValue()), x.getDerivative() * f(x.getValue()));
    }
}

#endif // AUTO_DIFFERENTIATION_HPP