#include <iostream>
#include "matrix.hpp"
#include <vector>

int main()
{
    std::vector<std::vector<double>> vec{{1}, {2}};
    std::vector<std::vector<double>> vec2{{1, 2}, {3, 4}};
    Matrix A(vec);
    Matrix B(vec2);
    std::cout << B << std::endl;
    aux(B);
    std::cout << B.inverse() * 2 * A;
    return 0;
}
