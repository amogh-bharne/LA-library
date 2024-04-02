#ifndef DIFFERENTIATION_HPP
#define DIFFERENTIATION_HPP

#include <cmath>
#include <functional>
#include <type_traits>

namespace linear_algebra {

    // Type trait to check if the type is a floating-point type
    template<typename T>
    struct is_floating_point : std::is_floating_point<T> {};

    template<typename T>
    class Differentiable {
    public:
        Differentiable(const T& value) : value_(value), derivative_(0) {}

        T Value() const { return value_; }
        T Derivative() const { return derivative_; }

        void SetDerivative(const T& derivative) { derivative_ = derivative; }

        // Operator overloads for common operations

        // Addition
        template<typename U>
        Differentiable<T> operator+(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ + other.Value());
        }

        // Subtraction
        template<typename U>
        Differentiable<T> operator-(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ - other.Value());
        }

        // Multiplication
        template<typename U>
        Differentiable<T> operator*(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ * other.Value());
        }

        // Division
        template<typename U>
        Differentiable<T> operator/(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ / other.Value());
        }

        // Exponentiation
        template<typename U>
        Differentiable<T> pow(const Differentiable<U>& other) const {
            return Differentiable<T>(std::pow(value_, other.Value()));
        }

        // Sine function
        Differentiable<T> sin() const {
            return Differentiable<T>(std::sin(value_));
        }

        // Cosine function
        Differentiable<T> cos() const {
            return Differentiable<T>(std::cos(value_));
        }

        // Logarithm function
        Differentiable<T> log() const {
            return Differentiable<T>(std::log(value_));
        }

    private:
        T value_;
        T derivative_;
    };

    // Template specialization for floating-point types
    template<typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
    class Differentiable{
    public:
        Differentiable(const T& value) : value_(value), derivative_(0) {}

        T Value() const { return value_; }
        T Derivative() const { return derivative_; }

        void SetDerivative(const T& derivative) { derivative_ = derivative; }

        // Operator overloads for common operations

        // Addition
        template<typename U>
        Differentiable<T> operator+(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ + other.Value());
        }

        // Subtraction
        template<typename U>
        Differentiable<T> operator-(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ - other.Value());
        }

        // Multiplication
        template<typename U>
        Differentiable<T> operator*(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ * other.Value());
        }

        // Division
        template<typename U>
        Differentiable<T> operator/(const Differentiable<U>& other) const {
            return Differentiable<T>(value_ / other.Value());
        }

        // Exponentiation
        template<typename U>
        Differentiable<T> pow(const Differentiable<U>& other) const {
            return Differentiable<T>(std::pow(value_, other.Value()));
        }

        // Sine function
        Differentiable<T> sin() const {
            return Differentiable<T>(std::sin(value_));
        }

        // Cosine function
        Differentiable<T> cos() const {
            return Differentiable<T>(std::cos(value_));
        }

        // Logarithm function
        Differentiable<T> log() const {
            return Differentiable<T>(std::log(value_));
        }

    private:
        T value_;
        T derivative_;
    };

    // Derivative function for unary functions
    template<typename T, typename F>
    Differentiable<T> differentiate(const Differentiable<T>& x, const F& func) {
        Differentiable<T> result(func(x.Value()));
        const T dx = 1e-6; // Small value for numerical differentiation
        const T x_plus_dx = x.Value() + dx;
        T derivative = (func(x_plus_dx) - func(x.Value())) / dx;
        result.SetDerivative(derivative);
        return result;
    }

    // Derivative function for binary functions
    template<typename T, typename F>
    Differentiable<T> differentiate(const Differentiable<T>& x, const Differentiable<T>& y, const F& func) {
        Differentiable<T> result(func(x.Value(), y.Value()));
        const T dx = 1e-6; // Small value for numerical differentiation
        const T dy = 1e-6;
        const T x_plus_dx = x.Value() + dx;
        const T y_plus_dy = y.Value() + dy;
        T derivative_x = (func(x_plus_dx, y.Value()) - func(x.Value(), y.Value())) / dx;
        T derivative_y = (func(x.Value(), y_plus_dy) - func(x.Value(), y.Value())) / dy;
        result.SetDerivative(derivative_x + derivative_y);
        return result;
    }

} // namespace linear_algebra

#endif // DIFFERENTIATION_HPP
