// main.cpp

#include <iostream>
#include "../include/linear_algebra/vector.hpp"
#include "../include/linear_algebra/matrix.hpp"
#include "../include/linear_algebra/auto_differentiation.hpp"


using namespace linear_algebra;

int main() {

    //use all the different libraries

    Matrix<float,3,3> m1({{1,1,2},{3.5,4,3.3},{4.2,3.8,1.2}});

    // Vector<float,3> v1({1,2,2});

    // auto solution = m1.solve_linear_equations(v1);

    // std :: cout<<solution;

    // Matrix<float,3,3> m2({{1,2,3},{1,2,3},{1,2,3}});

    // auto m3=m1+m2;

    // auto m4=m1*m2;

    // m4.display();

    // m3.display();

    Matrix<float,3,1> m2({{3.5},{4.2},{3}});

    auto mul=m1*m2;

    mul.display();



    Matrix <float,10,10> mat({{5.779 ,6.957 ,3.980 ,7.435 ,1.379 ,4.028 ,1.551 ,3.405 ,3.664 ,5.879},
                            {3.904 ,0.909 ,4.064 ,7.280 ,8.309 ,2.144 ,1.173 ,7.608 ,8.013 ,4.761},
                            {4.269 ,6.047 ,7.750 ,7.829 ,0.942 ,3.915 ,2.624 ,7.300 ,6.157 ,8.809},
                            {4.555 ,6.903 ,0.202 ,2.271 ,4.685 ,8.331 ,5.426 ,3.868 ,6.008 ,0.700},
                            {1.332 ,3.925 ,7.908 ,4.269 ,8.914 ,2.417 ,1.331 ,2.794 ,8.301 ,0.072},
                            {4.478 ,1.491 ,5.827 ,7.712 ,4.020 ,3.197 ,2.972 ,7.143 ,1.214 ,6.520},
                            {3.637 ,3.263 ,5.237 ,1.762 ,5.779 ,1.571 ,6.319 ,1.590 ,1.648 ,2.995},
                            {7.794 ,6.046 ,6.523 ,3.135 ,7.269 ,5.776 ,1.014 ,2.279 ,5.821 ,4.386},
                            {4.163 ,8.056 ,8.283 ,8.825 ,8.019 ,7.014 ,3.724 ,2.940 ,3.851 ,2.887},
                            {7.113 ,3.057 ,2.377 ,8.037 ,0.816 ,7.563 ,2.846 ,6.900 ,2.067 ,8.304}
});

    mat.inverse().display();
    return 0;

}
