#include "../include/linear_algebra/matrix.hpp"

int main() {

    using namespace linear_algebra;
    // Test default constructor
    Matrix<double, 3, 3> mat_default;
    mat_default.display();
    
    // Test constructor with initializer list
    Matrix<double, 2, 2> mat_init = {{1.4, 2.4}, {3.44, 4.3}};
    mat_init.display();

    // Test addition
    Matrix<double, 2, 2> mat_a = {{1.0, 2.0}, {3.0, 4.0}};
    Matrix<double, 2, 2> mat_b = {{5.0, 6.0}, {7.0, 8.0}};
    auto mat_sum = mat_a + mat_b;
    mat_sum.display();

    // Test multiplication
    Matrix<double, 2, 2> mat_c = {{1.0, 2.0}, {3.0, 4.0}};
    Matrix<double, 2, 2> mat_d = {{5.0, 6.0}, {7.0, 8.0}};
    auto mat_product = mat_c * mat_d;
    mat_product.display();

    // Test scalar multiplication
    auto scalar_result = mat_c * 2.0;
    scalar_result.display();

    // Test transpose
    auto transposed_mat = mat_c.transpose();
    transposed_mat.display();

    // Test inverse
    Matrix<double, 2, 2> singular_mat = {{1.0, 2.0}, {1.0, 2.0}};
    auto inversed_mat = mat_c.inverse();
    inversed_mat.display();

    // Test determinant
    double det = mat_c.determinant();
    std::cout << "Determinant of mat_c: " << det << std::endl;

    // Test Frobenius norm
    double norm = mat_c.norm();
    std::cout << "Frobenius norm of mat_c: " << norm << std::endl;

    // Test solving linear equations
    Vector<double, 2> b ({5.0, 11.0});
    auto solution = mat_c.solve_linear_equations(b);
    std::cout << "Solution of linear equations:" << std::endl;
    std::cout<<solution;

    return 0;
}
