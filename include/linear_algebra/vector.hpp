#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <initializer_list>
#include <cmath>
#include <type_traits>

namespace linear_algebra {

    // Type trait to check if all types in a parameter pack are arithmetic
    template<typename... Args>
    struct are_arithmetic : std::conjunction<std::is_arithmetic<Args>...> {};

    template<typename T, size_t size>
    class Vector {
    public:
        // Constructors
        Vector();
        Vector(const T& value);
        Vector(const std::initializer_list<T>& list);
        template<typename... Args,
                 typename = std::enable_if_t<are_arithmetic<Args...>::value>>
        Vector(Args... args);
        Vector(const Vector& other);
        
        // Destructor
        ~Vector();
        
        // Assignment operator
        Vector& operator=(const Vector& other);
        
        // Access operators
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        
        // Other methods
        size_t Size() const;
        void Print() const;

        // Friend declaration for scalar multiplication
        template<typename U>
        friend Vector<T, size> operator*(const U& scalar, const Vector<T, size>& vec);

    private:
        T data[size];
    };

    // Implementation of methods

    // Default constructor
    template<typename T, size_t size>
    Vector<T, size>::Vector() : data{} {}

    // Constructor with a single value
    template<typename T, size_t size>
    Vector<T, size>::Vector(const T& value) {
        std::fill(data, data + size, value);
    }

    // Constructor with initializer list
    template<typename T, size_t size>
    Vector<T, size>::Vector(const std::initializer_list<T>& list) {
        size_t i = 0;
        for (const auto& val : list) {
            if (i >= size) break;
            data[i++] = val;
        }
    }

    // Constructor with variadic arguments
    template<typename T, size_t size>
    template<typename... Args,
             typename>
    Vector<T, size>::Vector(Args... args) {
        static_assert(sizeof...(args) == size, "Number of arguments must match the size of the vector");
        size_t i = 0;
        ((data[i++] = args), ...);
    }

    // Copy constructor
    template<typename T, size_t size>
    Vector<T, size>::Vector(const Vector& other) {
        std::copy(other.data, other.data + size, data);
    }

    // Destructor
    template<typename T, size_t size>
    Vector<T, size>::~Vector() {}

    // Assignment operator
    template<typename T, size_t size>
    Vector<T, size>& Vector<T, size>::operator=(const Vector& other) {
        if (this != &other) {
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    // Access operator
    template<typename T, size_t size>
    T& Vector<T, size>::operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Const access operator
    template<typename T, size_t size>
    const T& Vector<T, size>::operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Size method
    template<typename T, size_t size>
    size_t Vector<T, size>::Size() const {
        return size;
    }

    // Print method
    template<typename T, size_t size>
    void Vector<T, size>::Print() const {
        std::cout << "[ ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "]" << std::endl;
    }

    // Scalar multiplication operator
    template<typename T, size_t size, typename U>
    Vector<T, size> operator*(const U& scalar, const Vector<T, size>& vec) {
        Vector<T, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = scalar * vec[i];
        }
        return result;
    }

} // namespace linear_algebra

#endif // VECTOR_HPP
