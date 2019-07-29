
#include "jakobi.hpp"
#include <iostream>

int main()
{

    Matrix A = {{10., -1., 2., 0.},
                {-1., 11., -1., 3.},
                {2., -1., 10., -1.},
                {0.0, 3., -1., 8.}};

    Vector b = {6., 25., -11., 15.};
    Vector x = {0., 0., 0., 0.};

    SolveJakobiMethod(A, b, x);
     

    for (int i = 0; i < x.size(); ++i) {
        std::cout << x[i] << ", ";
    }
    std::cout << std::endl;
    return 0;
}
