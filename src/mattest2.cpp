#include "../include/linear_algebra/matrix.hpp"

#include <iostream>

using namespace linear_algebra;

int main()
{
    Matrix<int,3,3> mat({{1,2,3},{4,5,6},{7,8,9}});
    Vector<int,3> vec({1,2,3});

    //multiply

    Vector<int,3> res;

    res=mat*vec;

    std::cout<<res;

}