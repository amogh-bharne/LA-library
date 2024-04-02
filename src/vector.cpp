#include "vector.hpp"

namespace linear_algebra {

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

    // Explicit instantiations for common types
    template class Vector<int, 3>;
    template class Vector<float, 3>;
    template class Vector<double, 3>;

} // namespace linear_algebra
