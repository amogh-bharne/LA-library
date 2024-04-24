//Contains implementation for Vector class

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath> 
#include <type_traits> 
#include <ostream>
#include <functional>

namespace linear_algebra {

    template<typename T, size_t N>
    class Vector {
    public:
        // Constructors
        Vector();
        Vector(const T (&arr)[N]);

        // Basic operations
        Vector<T, N> operator+(const Vector<T, N>& other) const;
        Vector<T, N> operator-(const Vector<T, N>& other) const;
        Vector<T, N> operator*(T scalar) const;

        T& operator[]( int index) {
            return data[index];
        }

        const T& operator[]( int index) const {
            return data[index];
        }
        T dot(const Vector<T, N>& other) const;

        // Cross product (for 3D vectors)
        template<typename U = T>
        Vector<T, 3> cross(const Vector<U, 3>& other) const;

        // Normalization
        Vector<T, N> normalize() const;

        // Magnitude
        T magnitude() const;

        template<typename U, size_t S>
        friend std::ostream& operator<<(std::ostream& os, const Vector<U, S>& vec);

        template<typename... Vectors>
        static Vector<T, N> add(const Vector<T, N>& first, const Vectors&... others);

        template <typename... ScalarVectorPairs>
        static Vector<T, N> linearCombination(const ScalarVectorPairs&... scalarVectorPairs);

        auto square() const {
            return [this]<typename U>(Vector<U, N> v) {
                Vector<U, N> result;
                for (size_t i = 0; i < N; ++i) {
                    result[i] = v[i] * v[i];
                }
                return result;
            }(*this);
        }

        auto cube() const {
            return [this]<typename U>(Vector<U, N> v) {
                Vector<U, N> result;
                for (size_t i = 0; i < N; ++i) {
                    result[i] = v[i] * v[i] * v[i];
                }
                return result;
            }(*this);
        }

        auto transform(const std::function<T(T)>& func) const {
            return [this, func]<typename U>(Vector<U, N> v) {
                Vector<U, N> result;
                for (size_t i = 0; i < N; ++i) {
                    result[i] = func(v[i]);
                }
                return result;
            }(*this);
        }
    
        
    private:
        T data[N];
    };

    // Constructors
    template<typename T, size_t N>
    Vector<T, N>::Vector() {
        // Initialize all elements to zero
        for (size_t i = 0; i < N; ++i) {
            data[i] = T();
        }
    }

    template<typename T, size_t N>
    Vector<T, N>::Vector(const T (&arr)[N]) {
        // Copy the array into the vector data
        for (size_t i = 0; i < N; ++i) {
            data[i] = arr[i];
        }
    }

    template<typename T, size_t N>
    template<typename... Vectors>
    Vector<T, N> Vector<T, N>::add(const Vector<T, N>& first, const Vectors&... others) {
        Vector<T, N> result = first;
        (void)std::initializer_list<int>{(result = result + others, 0)...};
        return result;
    }

    template<typename T, size_t N> 
     std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec){
        os << "(";
        for (size_t i = 0; i < N; ++i) {
            os << vec[i];
            if (i != N - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
        }

    // Basic operations
    template<typename T, size_t N>
    Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& other) const {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    template<typename T, size_t N>
    Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& other) const {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    template<typename T, size_t N>
    Vector<T, N> Vector<T, N>::operator*(T scalar) const {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    template<typename T, size_t N>
    T Vector<T, N>::dot(const Vector<T, N>& other) const {
        T result = T();
        for (size_t i = 0; i < N; ++i) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    // Cross product, specialized only for 3D vectors
    template<typename T, size_t N>
    template<typename U>
    Vector<T, 3> Vector<T, N>::cross(const Vector<U, 3>& other) const {
        static_assert(N == 3, "Cross product is only defined for 3D vectors");
        Vector<T, 3> result;
        result.data[0] = data[1] * other.data[2] - data[2] * other.data[1];
        result.data[1] = data[2] * other.data[0] - data[0] * other.data[2];
        result.data[2] = data[0] * other.data[1] - data[1] * other.data[0];
        return result;
    }

    // Normalization
    template<typename T, size_t N>
    Vector<T, N> Vector<T, N>::normalize() const {
        T mag = magnitude();
        if (mag == T(0)) {
            return *this;
        }
        return *this * (T(1) / mag);
    }

    // Magnitude
    template<typename T, size_t N>
    T Vector<T, N>::magnitude() const {
        T sum_sq = T();
        for (size_t i = 0; i < N; ++i) {
            sum_sq += data[i] * data[i];
        }
        return std::sqrt(sum_sq);
    }

    // Linear combination
    template<typename T, size_t N>
    template <typename... ScalarVectorPairs>
    Vector<T, N> Vector<T, N>::linearCombination(const ScalarVectorPairs&... scalarVectorPairs) {
        Vector<T, N> result;
        linearCombinationHelper(result, scalarVectorPairs...);
        return result;
    }

    template<typename T, size_t N>
    void linearCombinationHelper(Vector<T, N>& result) {
        // no pairs
    }

    template<typename T, size_t N, typename... Rest>
    void linearCombinationHelper(Vector<T, N>& result, T scalar, const Vector<T, N>& vec, const Rest&... rest) {
        for (size_t i = 0; i < N; ++i) {
            result[i] += scalar * vec[i];
        }
        linearCombinationHelper(result, rest...);
    }



} 

#endif 
