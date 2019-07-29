
#include "jakobi.hpp"

#include <iostream>
#include <algorithm>

bool CheckAcurracy(const Vector& x1, const Vector& x2, const double eps)
{
    if (x1.size() != x2.size()) { return false; }
    for (int i = 0; i < x1.size(); ++i) {
        if (std::abs(x1[i] - x2[i]) > eps) { return false; }
    }
    return true;
}

void SolveJakobiMethod(const Matrix& A, const Vector& b, Vector& x)
{
    Vector tmp(x.size());
    const size_t ITER_COUNT = 10000;
    for (int iter = 0; iter < ITER_COUNT; ++iter) {
        size_t n = b.size();
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            tmp[i] = (b[i] - sum) / A[i][i];
        }

        std::cout << "Iteration: " << iter << " Sol : ";

        if (CheckAcurracy(x, tmp, 0.000000000001)) {
            break;
        }

        x = tmp;

        for (int i = 0; i < x.size(); ++i) {
            std::cout << x[i] << ", ";
        }
        std::cout << std::endl;
    }
}


void SolveGaussZeidelMethod(const Matrix& A, const Vector& b, Vector& x)
{
    Vector tmp(x.size());
    const size_t ITER_COUNT = 10000;
    for (int iter = 0; iter < ITER_COUNT; ++iter) {

    }
}

